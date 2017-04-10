#include <stdio.h> 
#include <iostream>
#include "opencv_tools.h"

using namespace cv;
using namespace std;

int main()
{        
    Mat gray, threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
	Mat image = cv::imread("sample_img/doremon.jpg", CV_LOAD_IMAGE_COLOR);
    Mat result(image);
	if (!image.data)
	{
        std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}		
    namedWindow("Original Image", CV_WINDOW_NORMAL);
    resizeWindow("Original Image", 600, 600);
	imshow("Original Image", image);
    cvtColor(image, gray, CV_BGR2GRAY);

    // Detect edge using threshold
    threshold(gray, threshold_output, 80, 255, CV_THRESH_BINARY_INV);

    // Find contours
    findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // Find the convex hull for each contours
    vector<vector<Point> > hull(contours.size());
    for (int i = 0; i < contours.size(); ++i) {
        convexHull(Mat(contours[i]), hull[i], false);
    }

    // Draw contours
    // thickness = -1: Fill color on convex hull
    for( int i = 0; i< contours.size(); i++ )
    {
        drawContours(result, contours, i,CV_RGB(255,0,0), -1,8, vector<Vec4i>(), 0, Point());
        drawContours(result, hull, i, CV_RGB(255, 0, 0),-1,8, vector<Vec4i>(), 0, Point());
    }
    namedWindow("Result Image", CV_WINDOW_NORMAL);
    resizeWindow("Result Image", 600, 600);
    imshow("Result Image", result);
    waitKey(0);
	return 0;
}
