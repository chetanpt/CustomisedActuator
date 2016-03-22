#include <OpenSim/OpenSim.h>
#include <ctime>    // for clock()
#include "Trial.h"

using namespace OpenSim;
using namespace SimTK;
using namespace std;

void trial::trialMethod(){
	/*
	1. Trying to add muscle (internal, external(pathspring) to the model)
	2. Finding jacobian matrix/moment arm of the model 

	*/
	/*
	cout << "IN trial class" << "\n";
	String modelData = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01.osim";
	Model osimModel(modelData);
	State& si = osimModel.initSystem();
	cout << si << "\n";
	cout << si.getNumSubsystems() << "\n";
	*/

	double doubleD;
	doubleD = -10;
	double * doubleS ;
	cout << doubleD << "\n"; // -10
	doubleS = &doubleD;
	cout << &doubleS << "\n";// address
	cout << *doubleS << "\n";  // -10
	*doubleS = -20;
	cout << doubleD << "\n"; //-20
	cout << *doubleS << "\n";  // -20
	double *doubleP = &doubleD;
	
	cout << *doubleS << " " << &doubleS << "\n";  // -20
	cout << *doubleP << " " << &doubleP << "\n";  // -30
	*doubleP = -30;
	// Copy pointer did not worked, some mistake has been made
	cout << doubleD << "\n"; //-20
	cout << *doubleS << " " << &doubleS << "\n";  // -20
	cout << *doubleP << " " << &doubleP << "\n";  // -30
	 
	// Now airthematics practicle
	char *cPointer;
	int *iPointer;
	long *lPointer;
	cout << &cPointer << " " << &iPointer << " " << &lPointer << "\n";
	cPointer = cPointer + 1;
	iPointer = iPointer + 1;
	lPointer = lPointer + 1;
	cout << &cPointer << " " << &iPointer << " " << &lPointer << "\n";
	//cout << &(++cPointer) << " " << &(++iPointer) << " " << &(++lPointer) << "\n";
}
