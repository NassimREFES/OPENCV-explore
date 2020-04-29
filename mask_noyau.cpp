#include <iostream>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv/cv.hpp>

using namespace cv;
using namespace std;

void sharpen(const Mat& img, Mat& res)
{
    CV_Assert(img.depth()==CV_8U);

    res.create(img.size(), img.type());
    const int channels = img.channels();

    for (int j = 1; j < img.rows-1; ++j) {
        const uchar* previous = img.ptr<uchar>(j-1);
        const uchar* current  = img.ptr<uchar>(j);
        const uchar* next     = img.ptr<uchar>(j+1);

        uchar* output = res.ptr<uchar>(j);

        for (int i = channels; i < channels*(img.cols-1); ++i) {
            *output++ = (5*current[i]-
            current[i-channels]-current[i+channels]-previous[i]-next[i]);
        }
    }

    res.row(0).setTo(Scalar(0));
    res.row(res.rows-1).setTo(Scalar(0));
    res.col(0).setTo(Scalar(0));
    res.col(res.cols-1).setTo(Scalar(0));
}

int main(int argc, char** argv)
{
    Mat img = imread("nn.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat sharpened_img;
    Mat sharpened_img2;

    Mat kern = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    cout << kern << '\n';

    namedWindow("img", WINDOW_AUTOSIZE);
    namedWindow("res", WINDOW_AUTOSIZE);
    namedWindow("res2", WINDOW_AUTOSIZE);

    //sharpen(img, sharpened_img);
    //sharpen(sharpened_img, sharpened_img2);

    cv::filter2D(img, sharpened_img, img.depth(), kern);
    cv::filter2D(sharpened_img, sharpened_img2, sharpened_img.depth(), kern);

    imshow("img", img);
    imshow("res", sharpened_img);
    imshow("res2", sharpened_img2);

    waitKey(0);

    unsigned char x = 128;
    cout << ~(x) << '\n';

    return 0;
}
