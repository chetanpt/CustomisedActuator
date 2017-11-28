#ifndef TRIAL
#define TRIAL
#include <string>

class trial{
public:
	std::string motionData, modelData, resultDir, settingsFile;
	void trialMethod();
	void pendulum();
};
#endif