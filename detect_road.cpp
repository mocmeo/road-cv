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

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    // Region of Interest
    cv::Rect roi;
    roi.x = 0;
    roi.y = int(frame_height * 3/4);
    roi.width = frame_width;
    roi.height = frame_height - roi.y;
    
    for(;;)
    {
        Mat frame, mask, denoised;
        Mat gray, hist, video, hsv, grayROI;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(7,7), 1.5, 1.5);

        // increase contrast
        equalizeHist(gray, hist);
        //add_gaussian_noise(gray);
        //medianBlur(gray, gray, 5);


        // add boundary for region of interest 
        cvtColor(gray, video, COLOR_GRAY2BGR);
        rectangle(video, Point(roi.x, roi.y), Point(roi.width, roi.y + roi.height), Scalar(0,255,0), 1);

        // Change color space to extract lane color
        cvtColor(video, hsv, COLOR_BGR2HSV);
        grayROI = hsv(roi);
        inRange(grayROI, Scalar(0,0,90), Scalar(255, 255,255), mask);

        // Length for lines to find
        int minLineLength = 30;
        int maxLineGap = 10;
        cv::Mat frameClone(frame);
        vector<Vec4i> lines;
        HoughLinesP(mask, lines, 1, CV_PI/180, 30, minLineLength, maxLineGap);

        Vec4i lineL = Vec4i(0, 0, 0, 0);
        Vec4i lineR = Vec4i(0, 0, 0, 0);

        for (int i = 0; i < lines.size(); ++i) {
            Vec4i l = lines[i];
            
            float x1 = l[0];
            float y1 = l[1];
            float x2 = l[2];
            float y2 = l[3];
            if (round(x2-x1) != 0) {
                float arctan = slope(x1, x2, y1, y2);
                float realX1 = x1 + roi.x;
                float realX2 = x2 + roi.x;
                float realY1 = y1 + roi.y;
                float realY2 = y2 + roi.y;
                if (realX1 < frame_width / 2 && realX2 < frame_width / 2)
                //if (round(arctan>=round(-150)) && round(arctan<=round(50))) 
                    if (distance(realX1, realX2, realY1, realY2) 
                            > get_length(lineL)) {
                        lineL = Vec4i(realX1, realX2, realY1, realY2);
                    }
                if (realX1 >= frame_width / 2 && realX2 >= frame_width / 2)
                //if (round(arctan>=round(20)) &&  round(arctan<=round(150)))
                    if (distance(realX1, realX2, realY1, realY2) 
                            > get_length(lineR)) {
                        lineR = Vec4i(realX1, realX2, realY1, realY2);
                    }
            }
        }

        // drawing on original frame
        draw_line(frameClone, lineL);
        draw_line(frameClone, lineR);
        //draw_rect(frameClone, lineL);
        //draw_rect(frameClone, lineR);
        Point midpointL = get_midpoint(lineL);
        Point midpointR = get_midpoint(lineR);
        Point centerP = get_midpoint(midpointL, midpointR);
        draw_line(frameClone, midpointL, midpointR);
        draw_circle(frameClone, centerP);

        std::cout << centerP.x << " " << centerP.y << std::endl;

        imshow("frame", frameClone);
        waitKey(0);
    }
    
    cap.release();
    return 0;
}
