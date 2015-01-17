#include <iostream>
#include <string>
#include "src/header/solver/TSPSolver.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	//Used to check if CPlex runs to the end or there are some errors
	int computations = -1;

	//Path to file with the datas of the problem
	string dataFile = "";

	//Path to file with the problem saved by CPlex
	string problemFile = "";

	//Path to file with the solution of the problem produced by CPlex
	string resultFile = "";

	//CPlex TSP resolver
	TSPSolver *solver = 0;

	if((argc - 1) == 3)
	{
		//Read the path to file
		dataFile = argv[1];
		problemFile = argv[2];
		resultFile = argv[3];

		//Create the solver
		solver = new TSPSolver();

		//Lunch the solver
		computations = solver->resolve(dataFile, problemFile, resultFile);

		if(computations == 1)
		{
			cout << "RISOLUZIONE AVVENUTA CON SUCCESSO" << endl;
		}
		else
		{
			cout << "ERRORI DURANTE LA RISOLUZIONE" << endl;
		}
	}
	else
	{
		cout << "ATTEZIONE: parametri mancanti!!!" << endl;
		cout << "Per lanciare il solver sono richiesti i seguenti parametri:" << endl;
		cout << "1) path del file (.dat) contenente i dati del problema" << endl;
		cout << "2) path del file (.lp) dove verrà salvato il file con il problema" << endl;
		cout << "3) path del file (.sol) dove verrà salvata la soluzione trovata" << endl;
	}

	delete solver;
	return 0;
}