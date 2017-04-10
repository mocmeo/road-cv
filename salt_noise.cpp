#include <iostream>
#include <math.h>
#include "opencv_tools.h"

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
        Mat frame, mask, denoised;
        Mat gray, hist, video, hsv, grayROI;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(7,7), 1.5, 1.5);

        //salt(gray, 2000);
        sharpen2D(gray, gray);
        //add_gaussian_noise(gray);
        imshow("frame", gray);
        if(waitKey(30) >= 0) break;
    }
    
    cap.release();
    return 0;
}
