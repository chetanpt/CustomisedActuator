#include "graph.h"
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <math.h>



using namespace cv;
using namespace std;

#define w 400
#define yAxisInterval 10
#define boundryDisplacement 15

void graph::drawGraph(){
	double force[] = { 0, 10, 15, 12, 40, 12, 8, 0 };
	double time[] = { 0, 10, 20, 30, 40, 50, 60, 70 };

	double xSample = 1.5 * 60;
	double ySample = 93.9011;
	int xyZero[2] = { 20, 240 };

	double datInterval = 40 / 10 ;
	double pixelInterval = 240 / 10;
	double dataPixelRatio = pixelInterval / datInterval;

	double timeInterval = 70 / 10;
	double xPixelInterval = 360 / 10;
	double xDataPixelRatio = xPixelInterval / timeInterval;

	cout << "Max Force - " << 40 << "\n";
	cout << "Step Count - " << 10 << "\n";
	cout << "Data Interval on Y axis - " << datInterval << "\n";
	cout << "Pixel data Interval on Y axis - " << pixelInterval << "\n";
	cout << "dataPixel Ration - "<<dataPixelRatio << "\n";
	cout << "data value - " << force[2] << "	" << "Pixel Value" << dataPixelRatio * force[2] << "\n";

	

	char windowFrameName[] = "DrawingSample"; // Window Title 
	Mat image = Mat::zeros(w, w, CV_8UC3); // Create a image with black background
	/*
	Draw X-Y axis lines in the graph
	*/
	CvFont font;
	line(image, Point(20, 10), Point(20, 250), Scalar(100,100,100), 2, 8);
	line(image, Point(20, 250), Point(380, 250), Scalar(100, 100, 100), 2, 8);
	putText(image, "Time - (ms)", Point(300, 270), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(100, 100, 100), 1, 8, false);
	putText(image, "Muscle Forces - (N)", Point(5, 9), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(100, 100, 100), 1, 8, false);

	/*
	Draw Graph now with sample data
	*/
	
	double x[2] = {}, y[2] = {};
	for (size_t i = 0; i < 7; i++)
	{
		//_sleep(1000);
		line(image, Point((xDataPixelRatio * time[i] + 20), (250 -(dataPixelRatio * force[i])) ), Point(((xDataPixelRatio * time[i + 1]) + 20), (250 - dataPixelRatio * force[i + 1])), Scalar(100, 100, 100), 2, 8);
		cout << "Start - " << (xDataPixelRatio * time[i] + 20) << " , " << (250 - (dataPixelRatio * force[i]))  << " | Finish - " << (xDataPixelRatio * time[i + 1]) + 20 << " , " << (250 - dataPixelRatio * force[i + 1] ) << "\n";
		imshow(windowFrameName, image); // Show window with the drawing
		
	}
	
	waitKey(0); // This is most important part in opencv. Never miss this otherwise graphic window will hang/crash always
}
