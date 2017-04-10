#include <iostream>
#include <math.h>
#include "opencv_tools.h"

using namespace cv;
using namespace std;

int main()
{        
    Mat img = imread("sample_img/cat_01.jpg");
    if (!img.data) {
        cout << "File not found" << endl;
        return -1;
    }

    vector<cv::Mat> planes;
    cv::split(img, planes);
    colorReduce(img, 64);
    imshow("After effect", planes[2]);
    waitKey();
    return 0;
}
