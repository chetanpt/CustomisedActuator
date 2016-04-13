#ifndef CUST_SO
#define CUST_SO
#include <string.h>
#include <OpenSim/OpenSim.h>
#include <ctime>    // for clock()
#include <amp_graphics.h>
#include <conio.h>

using namespace OpenSim;
using namespace SimTK;
using namespace std;

class customSo{
	double getMaxFromList(Array<double>, String);
public:
	std::string motionData, modelData, resultDir, settingsFile;
	void runFixedOptimizatio();
	void muscleForceAnalysis();
	void viewModel();
	void insertMuscle();
};
#endif