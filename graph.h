#ifndef GRAPH
#define GRAPH
#include <string>


class graph{
public:
	std::string motionData, modelData, resultDir, settingsFile;
	void drawGraph();
	void drawAxisAndLabelIt();
};
#endif