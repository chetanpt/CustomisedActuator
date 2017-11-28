#include "graph.h"


/*
Requirements
1 - Muscle Name - Retrived
2 - Muscle Data (Activation/Force/Time) - Retrived
3 - Window Size (Provide Defaults, along with customised values) - TBD
4 - Define Axis displacement from boundry) - Done
5 - Define (0,0) - Done
6 - Time data (this can be set by setter function) - Retrived
*/
void graph::drawAxisAndLabelIt(double lastTime, double maxYaxis){
	double xSample = lastTime * 60;
	double ySample = 93.9011;
	int xyZero[2] = { 20, 240 };

	double datInterval = maxYaxis / 10;
	double pixelInterval = 240 / 10;
	yDataPixelRatio = pixelInterval / datInterval;

	double timeInterval = lastTime / 10;
	double xPixelInterval = 360 / 10;
	xDataPixelRatio = xPixelInterval / timeInterval;

	cout << "Max Force - " << maxYaxis<< "\n";
	cout << "Step Count - " << 10 << "\n";
	cout << "Data Interval on Y axis - " << datInterval << "\n";
	cout << "Pixel data Interval on Y axis - " << pixelInterval << "\n";
	cout << "dataPixel Ration - " << yDataPixelRatio << "\n";
	
	char windowFrameName[] = "DrawingSample"; // Window Title 
	
	/*
	Draw X-Y axis lines in the graph
	*/
	CvFont font;
	line(image, Point(20, 10), Point(20, 250), Scalar(100, 100, 100), 2, 8);
	line(image, Point(20, 250), Point(380, 250), Scalar(100, 100, 100), 2, 8);
	putText(image, "Time - (ms)", Point(300, 270), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(100, 100, 100), 1, 8, false);
	putText(image, "Muscle Forces - (N)", Point(5, 9), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(100, 100, 100), 1, 8, false);
	imshow("DisplayImage", image); // Show window with the drawing
	waitKey(realTimeGraphFeel); // This waitkey here gives feeling of plotting graph real time. But just the feeling as this is not realtime application yet
}
void graph::drawGraph(Array<double>& time, Array<double>& data){

	/*
	Draw Graph now with sample data
	*/
	
	for (size_t i = 0; i < data.getSize()-1; i++)
	{
		//_sleep(1000);
		/*
		The bug in this code - it tries to draw line for last value in the to the next values which is nothing but 0th position 
		in the graph. Need to avoid drawing this last line, since the data is not realtime but getting feed from optimization results. 
		*/
		line(image, Point((xDataPixelRatio * time[i] + 20), (250 -(yDataPixelRatio * data[i])) ), Point(((xDataPixelRatio * time[i + 1]) + 20), (250 - yDataPixelRatio * data[i + 1])), Scalar(100, 100, 100), 2, 8);
		//cout << "Start - " << (xDataPixelRatio * time[i] + 20) << " , " << (250 - (yDataPixelRatio * data[i]))  << " | Finish - " << (xDataPixelRatio * time[i + 1]) + 20 << " , " << (250 - yDataPixelRatio * data[i + 1] ) << "\n";
		imshow("DisplayImage", image); // Show window with the drawing
		
		waitKey(realTimeGraphFeel);
		
	}
	
	waitKey(0); // This is most important part in opencv. Never miss this otherwise graphic window will hang/crash always
}

void graph::drawDataGraph(Array<double>& time, Array<double>& data, double lastTime, double maxYaxis){
	VideoWriter wrt2("system.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30, Size(w, w), true);
	drawAxisAndLabelIt(lastTime, maxYaxis);
	
	drawGraph(time, data);
	wrt2.release();
}