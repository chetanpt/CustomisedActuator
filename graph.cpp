#include "graph.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

void graph::drawGraph(){
	Mat image;
	int flag = 1;
	image = imread("C:\\Users\\Bsys-\\Desktop\\test.jpg",flag);
	if (!image.data){
		cout << "Error reading image file." << endl;
	}
	namedWindow("ViewImage", WINDOW_KEEPRATIO);
	imshow("ViewImage", image);
	waitKey(0);
	
}