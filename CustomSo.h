#ifndef CUST_SO
#define CUST_SO
#include <string>


class customSo{
public:
	std::string motionData, modelData, resultDir, settingsFile;
	void runFixedOptimizatio();
	void muscleForceAnalysis();
	void viewModel();
};
#endif