#ifndef GRAPH
#define GRAPH
#include <string.h>
#include <OpenSim/OpenSim.h>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\calib3d\calib3d.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace OpenSim;
using namespace cv;


#define w 400
#define yAxisInterval 10
#define boundryDisplacement 15
#define realTimeGraphFeel 100


class graph{
public:
	double xDataPixelRatio, yDataPixelRatio;
	Array<double> xAxis, yAxis;
	cv::Mat image = cv::Mat::zeros(w, w, CV_8UC3); // Create a image with black background ;

	void drawGraph();
	void drawGraph(Array<double>& time, Array<double>& data);
	void drawDataGraph(Array<double>& time, Array<double>& data, double lastTime, double maxYaxix);
	void drawAxisAndLabelIt(double lastTime, double maxYaxis);
};
#endif