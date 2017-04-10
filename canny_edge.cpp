#include <stdio.h> 
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{        
	Mat image = cv::imread("sample_img/cat_01.jpg", CV_LOAD_IMAGE_COLOR);
	if (!image.data)
	{
		printf("Could not open or find the image\n");
		return -1;
	}		
	imshow("Original Image", image);

    Mat gray, draw, edge;
    cvtColor(image, gray, CV_BGR2GRAY);
    Canny( gray, edge, 100, 150, 3);
    edge.convertTo(draw, CV_8U);

    imshow("Canny Edge Detector", draw);

    waitKey(0);
	return 0;
}
