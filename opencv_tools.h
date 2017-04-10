#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
#define SQR(x) ((x)*(x))
const int thickness = 3;

// ------------- IMAGE TRANSFORMATION-------------
void sharpen2D(cv::Mat &image, cv::Mat &result) {
    cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
    kernel.at<float>(1,1)= 5.0;
    kernel.at<float>(0,1)= -1.0;
    kernel.at<float>(2,1)= -1.0;
    kernel.at<float>(1,0)= -1.0;
    kernel.at<float>(1,2)= -1.0;
    cv::filter2D(image,result,image.depth(),kernel);
}

void colorReduce(cv::Mat &image, int div=64) {
    int nl= image.rows; 
    int nc= image.cols * image.channels();
    for (int j=0; j<nl; j++) {
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<nc; i++) {
            data[i]=
                data[i]/div*div + div/2;
        }
    }
    //image = (image&cv::Scalar(212, 159, 123))
     //         + cv::Scalar(div/2, div/2, div/2); 
}

void add_gaussian_noise(cv::Mat &frame, double average=0.0, 
        double standard_deviation=10.0)
{
    // We need to work with signed images (as noise can be
    // negative as well as positive). We use 16 bit signed
    // images as otherwise we would lose precision.
    cv::Mat noise_image(frame.size(), CV_16SC1);
    randn(noise_image, Scalar::all(average), Scalar::all(standard_deviation));
    Mat temp_image;
    frame.convertTo(temp_image,CV_16SC1);
    addWeighted(temp_image, 1.0, noise_image, 1.0, 0.0, temp_image);
    temp_image.convertTo(frame,frame.type());
}

void salt(cv::Mat &image, int n) {
    cv::Mat_<uchar> grayImg = image;
    cv::Mat_<cv::Vec3b> colorImg = image;
    for (int k=0; k<n; k++) {
        int i= rand()%image.cols;
        int j= rand()%image.rows;
        if (image.channels() == 1) { // gray-level image
            //image.at<uchar>(j,i)= 255;
            grayImg(j,i) = 255;
        } else if (image.channels() == 3) { // color image
            colorImg(j,i)[0]= 255;
            colorImg(j,i)[1]= 255;
            colorImg(j,i)[2]= 255;
            //image.at<cv::Vec3b>(j,i)[0]= 255;
            //image.at<cv::Vec3b>(j,i)[1]= 255;
            //image.at<cv::Vec3b>(j,i)[2]= 255;
        }
    }
}


// --------------DRAWING FUNCTION----------------
float slope(float vx1, float vx2, float vy1, float vy2) {
    float m=float(vy2-vy1)/float(vx2-vx1);        //Slope equation
    float theta = atan(m);                  //calculate the slope angle
    return theta*(180/CV_PI);              //Calculated angle in radians
}

float distance(float vx1, float vx2, float vy1, float vy2) {
    float pX = SQR(vx2 - vx1);
    float pY = SQR(vy2 - vy1);
    return sqrt(pX + pY);
}

float get_length(Vec4i line) {
    float pX = SQR(line[0] - line[1]);
    float pY = SQR(line[2] - line[3]);
    return sqrt(pX + pY);
}

void draw_line(cv::Mat &frame, Vec4i line) {
    cv::line(frame, Point(line[0], line[2]),
                    Point(line[1], line[3]),
                    Scalar(0, 255, 0), thickness, 8, 0);
}

void draw_line(cv::Mat &frame, Point p1, Point p2) {
    cv::line(frame, p1, p2, Scalar(255, 0, 0), thickness, 8, 0);
}

void draw_rect(cv::Mat &frame, Vec4i line) {
    cv::rectangle(frame, Point(line[0], line[2]),
                    Point(line[1], line[3]),
                    Scalar(0, 255, 0), thickness, 8, 0);
}

void draw_circle(cv::Mat &frame, Point p) {
    int radius = 3;
    cv::circle(frame, p, radius, Scalar(0, 0, 255), thickness, 8, 0);
}

Point get_midpoint(Vec4i line) {
    float x = (line[0] + line[1]) / 2;
    float y = (line[2] + line[3]) / 2;
    return Point(x, y);
}

Point get_midpoint(Point p1, Point p2) {
    float x = (p1.x + p2.x) / 2;
    float y = (p1.y + p2.y) / 2;
    return Point(x, y);
}

