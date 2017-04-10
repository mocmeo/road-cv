#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{        
    VideoCapture cap("sample_vid/road1.avi");
    if (!cap.isOpened()) {
        return -1;
    }

    for(;;)
    {
        Mat frame, mask;
        Mat gray, hist, video, hsv, grayROI;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(7,7), 1.5, 1.5);

        // increase contrast
        equalizeHist(gray, hist);
        imshow("frame", frame);
        if(waitKey(30) >= 0) break;
    }
    
    cap.release();
    return 0;
}
