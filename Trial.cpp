#include <OpenSim/OpenSim.h>
#include <ctime>    // for clock()
#include <windows.h>
#include "Trial.h"

using namespace OpenSim;
using namespace SimTK;
using namespace std;

void trial::trialMethod(){
	/*
	1. Trying to add muscle (internal, external(pathspring) to the model)
	2. Finding jacobian matrix/moment arm of the model 

	*/
	cout << "IN trial class" << "\n";
	String modelData = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01.osim";
	Model osimModel(modelData);
	State& si = osimModel.initSystem();
	cout << si << "\n";
	cout << si.getNumSubsystems() << "\n";
	
}