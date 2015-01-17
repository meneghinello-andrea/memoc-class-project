#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "src/header/macro/cpxmacro.h"

using std::cout;
using std::endl;
using std::exception;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::string;
using std::vector;

class TSPSolver
{
	private:
		char errmsg[BUF_SIZE];
		int holes;
		int status;
		vector<double> *costs;

	protected:
		void printTime(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);
		int findIndex(int i, int j);
		
		void readProblemDatas(string fileName);
		void setObjectiveFunction(CEnv env, Prob lp);
		void setConstraint_1(CEnv env, Prob lp);
		void setConstraint_2(CEnv env, Prob lp);
		void setConstraint_3(CEnv env, Prob lp);
		void setConstraint_4(CEnv env, Prob lp);
		void setConstraint_5(CEnv env, Prob lp);

	public:
		TSPSolver();
		~TSPSolver();

		int resolve(string dataFile, string problemFile, string resultFile);
};

#endif //TSP_SOLVER_H