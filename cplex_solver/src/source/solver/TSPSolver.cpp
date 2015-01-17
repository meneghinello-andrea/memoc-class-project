#include "src/header/solver/TSPSolver.h"

TSPSolver::TSPSolver()
{
	this->costs = new vector<double>();
}

TSPSolver::~TSPSolver()
{
	delete this->costs;
}

int TSPSolver::resolve(string dataFile, string problemFile, string resultFile)
{
	int result = -1;

	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;

	if(resultFile != "")
	{
		try
		{
			//Read the problem datas from a .dat files
			this->readProblemDatas(dataFile);

			//Environment initialization
			DECL_ENV(env);
			DECL_PROB(env, lp);

			//Setup the objective function
			this->setObjectiveFunction(env, lp);

			//Setup the problem constraints
			this->setConstraint_1(env, lp);
			this->setConstraint_2(env, lp);
			this->setConstraint_3(env, lp);
			this->setConstraint_4(env, lp);
			this->setConstraint_5(env, lp);

			if(problemFile != "")
			{
				//Print the file with the problem
				CHECKED_CPX_CALL(CPXwriteprob, env, lp, problemFile.c_str(), NULL);
			}

			//Save the time before the problem is resolved
			start = std::chrono::system_clock::now();

			//Resolve the problem
			CHECKED_CPX_CALL(CPXmipopt, env, lp);

			//Save the time after the problem is solved
			end = std::chrono::system_clock::now();

			if(resultFile != "")
			{
				//Print the file with the result of the problem
				CHECKED_CPX_CALL(CPXsolwrite, env, lp, resultFile.c_str());
			}

			//Environment finalization
			CPXfreeprob(env, &lp);
			CPXcloseCPLEX(&env);

			//Print the time spent in search of the solution
			this->printTime(start, end);

			result = 0;
		}
		catch(exception &ex)
		{
			cout << "EXCEPTION -> " << ex.what() << endl;
			result = -1;
		}
	}
	return result;
}

void TSPSolver::printTime(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end)
{
	//Milliseconds used by the computations
	int elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	//Datas to print the start and the end time
	std::time_t startTime = std::chrono::system_clock::to_time_t(start);
	std::time_t endTime = std::chrono::system_clock::to_time_t(end);

	cout << "Computation started at:   " << std::ctime(&startTime) << endl;
	cout << "Computation completed at: " << std::ctime(&endTime) << endl;
	cout << "Computation in (ms):      " << elapsedMilliseconds << endl;
}

int TSPSolver::findIndex(int i, int j)
{
	//Number of empty space in the matrix associated to the linearized array
	int empty_space_read = 0;

	//Index of the cost in the linearized array
	int index = 0;

	//Row start in the matrix associated with the linearized array
	int row_start = 0;

	if (i < j)
	{
		//index calculation for the lower triangular matrix
		row_start = (this->holes * i) - ((i * (i + 1)) / 2);
		empty_space_read = i + 1;
		index = row_start - empty_space_read + j;
	}
	else
	{
		//Index calculation for the the upper triangular matrix
		row_start = (this->holes * j) - ((j * (j + 1)) / 2);
		empty_space_read = j + 1;
		index = row_start - empty_space_read + i;
	}

	return index;
}

void TSPSolver::readProblemDatas(string fileName)
{
	double cost = 0;
	ifstream file;
	string line = "";

	if(fileName != "")
	{
		file.open(fileName.c_str());

		//Read the number of holes in the plate
		getline(file, line);
		istringstream iss(line);
		iss >> this->holes;

		//Read the problem's data
		while(getline(file, line))
		{
			istringstream iss(line);
			iss >> cost;
			this->costs->push_back(cost);
		}

		file.close();
	}
}

void TSPSolver::setObjectiveFunction(CEnv env, Prob lp)
{
	//Used to setup the variables name in the output file
	const int SIZE = 512;
	char name[SIZE] = {};
	char *variable_name = (char*)(&name[0]);

	//Used to setup the variable's type
	char x_type = 'I';
	char y_type = 'B';

	//Used to setup the coefficient of the variables in the objective function
	double coefficient[1] = {};

	//Used to setup the bound of the variables
	double lower_bound = -CPX_INFBOUND;
	double upper_bound = CPX_INFBOUND;

	//Setup the Y_i_j variables (except the Y_i_i variables)
	lower_bound = 0.0;
	upper_bound = 1.0;
	for(int i = 0; i < this->holes; i++)
	{
		for(int j = 0; j < this->holes; j++)
		{
			if(i != j)
			{
				snprintf(name, SIZE, "Y_%i_%i", i, j);
				CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &(this->costs->at(this->findIndex(i, j))), &lower_bound, &upper_bound, &y_type, &variable_name);
			}
		}
	}

	//Setup the X_i_j variables (except the X_i_i variables)
	coefficient[0] = 0.0;
	lower_bound = 0.0;
	upper_bound = CPX_INFBOUND;
	for(int i = 0; i < this->holes; i++)
	{
		for(int j = 0; j < this->holes; j++)
		{
			if(i != j)
			{
				snprintf(name, SIZE, "X_%i_%i", i, j);
				CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &coefficient[0], &lower_bound, &upper_bound, &x_type, &variable_name);
			}
		}
	}
}

void TSPSolver::setConstraint_1(CEnv env, Prob lp)
{
	//Sense of the constraint (L = lower_or_equals - E = equals - G = grather_or_equals)
	char sense = 'E';

	//Vector with the right side term of the constraint
	double rhs[1] = {};
	rhs[0] = this->holes;

	//Start index of the constraints datas in the vector
	int mat_beg = 0;

	//Pointer to the first X_i_j variable in the linearized array
	int x_starter = (this->holes - 1) * this->holes;

	//Indexes of the variables in the constraint
	vector<int> indexes(this->holes - 1);

	//Coefficient of the variables in the constraint
	vector<double> coefficients(this->holes - 1);

	for(int i = 0; i < (this->holes - 1); i++)
	{
		indexes.push_back(x_starter + i);
		coefficients.push_back(1.0);
	}

	//Add the constraints to the problem
	CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, indexes.size(), &rhs[0], &sense, &mat_beg, &indexes[0], &coefficients[0], NULL, NULL);
}

void TSPSolver::setConstraint_2(CEnv env, Prob lp)
{
	//Sense of the constraints (L = lower_or_equals - E = equals - G = grather_or_equals)
	char sense = 'E';

	//Vector with the right side term of the constraint
	double rhs[1] = {};
	rhs[0] = 1.0;

	//Start index of the constraints datas in the vector
	int mat_beg = 0;

	//Pointer to the first X_i_j variable in the linearized array
	int x_starter = (this->holes - 1) * this->holes;

	//Indexes of the variables in the constraint
	vector<int> indexes(2 * (this->holes - 1));

	//Coefficient of the variables in the constraint
	vector<double> coefficients(2 * (this->holes - 1));

	for(int i = 1, j = (this->holes - 1), idx = 0; i < this->holes; i++, j += (this->holes - 1), idx = 0)
	{
		//Add the indexes of the positive variables in the constraint
		for(int k = 0, l = 0; k < this->holes; k++, l++)
		{
			if(i != k)
			{
				idx = x_starter + (this->holes * k) + i - l;
				if(i > k)
				{
					idx -= 1;
				}
				indexes.push_back(idx);
				coefficients.push_back(1.0);
			}
		}

		//Add the indexes of the negative variables in the constaint
		for(int k = 0, l = 0; k < this->holes; k++)
		{
			if(i != k)
			{
				indexes.push_back(x_starter + j + l);
				coefficients.push_back(-1.0);
				l += 1;
			}
		}

		//Add the constraints to the problem
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, indexes.size(), &rhs[0], &sense, &mat_beg, &indexes[0], &coefficients[0], NULL, NULL);

		//Clear the vector for the new constraint
		indexes.clear();
		coefficients.clear();
	}
}

void TSPSolver::setConstraint_3(CEnv env, Prob lp)
{
	//Sense of the constraint (L = lower_or_equals - E = equals - G = grather_or_equals)
	char sense = 'E';

	//Vector with the right side term of the constraint
	double rhs[1] = {};
	rhs[0] = 1.0;

	//Start index of the constraints datas in the vector
	int mat_beg = 0;

	//Indexes of the variables in the constraint
	vector<int> indexes(this->holes - 1);

	//Coefficients of the variables in the constraint
	vector<double> coefficients(this->holes - 1);

	for(int i = 0, j = 0; i < this->holes; i++, j += (this->holes - 1))
	{
		for(int k = 0, l = 0; k < this->holes; k++)
		{
			if(i != k)
			{
				indexes.push_back(j + l);
				coefficients.push_back(1.0);
				l += 1;
			}
		}

		//Add the constraints to the problem
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, indexes.size(), &rhs[0], &sense, &mat_beg, &indexes[0], &coefficients[0], NULL, NULL);

		//Clear the vectors for the new constraint
		indexes.clear();
		coefficients.clear();
	}
}

void TSPSolver::setConstraint_4(CEnv env, Prob lp)
{
	//Sense of the constraint (L = lower_or_equals - E = equals - G = grather_or_equals)
	char sense = 'E';

	//Vector with the right side term of the constraint
	double rhs[1] = {};
	rhs[0] = 1.0;

	//Start index of the constraint datas in the vectors
	int mat_beg = 0;

	//Indexes = of the variables in the constraint
	vector<int> indexes(this->holes - 1);

	//Coefficients of the variables in the constraint
	vector<double> coefficients(this->holes - 1);

	for(int i = 0, idx = 0; i < this->holes; i++, idx = 0)
	{
		for(int j = 0, k = 0; j < this->holes; j++, k++)
		{
			if(i != j)
			{
				idx = (this->holes * j) + i - k;
				if(i > j)
				{
					idx -= 1;
				}
				indexes.push_back(idx);
				coefficients.push_back(1.0);
			}
		}

		//Add the constraint to the problem
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, indexes.size(), &rhs[0], &sense, &mat_beg, &indexes[0], &coefficients[0], NULL, NULL);

		//Clear the vectors for the new constraint
		indexes.clear();
		coefficients.clear();
	}
}

void TSPSolver::setConstraint_5(CEnv env, Prob lp)
{
	//Sense of the constraint (L = lower_or_equals - E = equals - G = grather_or_equals)
	char sense = 'L';

	//Vector with the right side term of the constraint
	double rhs[1] = {};
	rhs[0] = 0.0;

	//Start index of the constraints data in the vector
	int mat_beg = 0;

	//Pointer to the first X_i_j variable in the linearized array
	int x_starter = (this->holes - 1) * this->holes;

	//Indexes of the variables in the constraint
	vector<int> indexes(2);

	//Coefficients of the variables in the constraint
	vector<double> coefficients(2);

	for(int i = 0; i < ((this->holes - 1) * this->holes); i++)
	{
		//Setup the X_i_j variables
		indexes.push_back(x_starter + i);
		coefficients.push_back(1.0);

		//Setup the Y_i_j variables
		indexes.push_back(i);
		coefficients.push_back(-this->holes);

		//Add the constraint to the problem
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, indexes.size(), &rhs[0], &sense, &mat_beg, &indexes[0], &coefficients[0], NULL, NULL);

		//Clear the vectors for the next constraint
		indexes.clear();
		coefficients.clear();
	}
}