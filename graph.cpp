#include "graph.h"
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <math.h>

#define w 400

using namespace cv;
using namespace std;

void graph::drawGraph(){
	double force[] = { 0, 10, 15, 12, 40, 12, 8, 0 };

	double xSample = 1.5 * 60;
	double ySample = 93.9011;
	int xyZero[2] = { 20, 240 };

	double datInterval = 40 / 10 ;
	double pixelInterval = 240 / 10;
	double dataPixelRatio = pixelInterval / datInterval;

	cout << "Max Force - " << 40 << "\n";
	cout << "Step Count - " << 10 << "\n";
	cout << "Data Interval on Y axis - " << datInterval << "\n";
	cout << "Pixel data Interval on Y axis - " << pixelInterval << "\n";
	cout << "dataPixel Ration - "<<dataPixelRatio << "\n";
	cout << "data value - " << force[2] << "	" << "Pixel Value" << dataPixelRatio * force[2] << "\n";



	//cout << "x axis unit steps " << (int)(360 / xSample) << "\n";
	//cout << "y axis unit steps " << (int)round(240 / xSample) << "\n";
	//	type casting double to int at the same time rounding it to the nearest int value
	//	int y = (int)round(x);

	char windowFrameName[] = "DrawingSample"; // Window Title 
	Mat image = Mat::zeros(w, w, CV_8UC3); // Create a image with black background
	/*
	Draw X-Y axis lines in the graph
	*/
	line(image, Point(20, 10), Point(20, 250), Scalar(100,100,100), 2, 8);
	line(image, Point(20, 250), Point(380, 250), Scalar(100, 100, 100), 2, 8);

	/*
	Data_Interval_x = max_value_Y_axis / Intervals
	pixel_intervals_x = x_axis_pixel_length / Data_Interval

	Data_Interval_y = max_value_X_axis / Intervals
	pixel_intervals_y = x_axis_pixel_length / Data_Interval 
	*/
	
	
	imshow(windowFrameName, image); // Show window with the drawing
	waitKey(0); // This is most important part in opencv. Never miss this otherwise graphic window will hang/crash always

	
}