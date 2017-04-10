#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


void add_gaussian_noise(cv::Mat &frame, double average=0.0,
        double standard_deviation=10.0)
{
    cv::Mat noise_image(frame.size(), CV_16SC1);
    randn(noise_image, Scalar::all(average), Scalar::all(standard_deviation));
    Mat temp_image;
    frame.convertTo(temp_image,CV_16SC1);
    addWeighted(temp_image, 1.0, noise_image, 1.0, 0.0, temp_image);
    temp_image.convertTo(frame,frame.type());
}

int main() {

    Mat img = imread("sample_img/cat_01.jpg");

    if (!img.data) {
        cout << "File not found" << endl;
        return -1;
    }

    // first copy the image
    Mat img_gray = img.clone();
    cvtColor(img, img_gray, CV_RGB2GRAY);
    
    add_gaussian_noise(img_gray);

    Mat img1;
    cv::fastNlMeansDenoising(img_gray, img1, 15.0, 7, 21);

    imshow("img1", img1);

    waitKey();

    return 0;
}
