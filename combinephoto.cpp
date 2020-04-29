#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;

void copy_(Mat& dst, const Mat& src, const int from, const int to)
{
    Mat_<Vec3b> _src = src;
    Mat_<Vec3b> _dst = dst;
    for (int i = from; i < to; ++i) {
        for (int j = 0; j < src.rows; ++j) {
            _dst(j, i)[0] = _src(j, i)[0];
            _dst(j, i)[1] = _src(j, i)[1];
            _dst(j, i)[2] = _src(j, i)[2];
        }
    }
}

int main(int argc, char** argv)
{
    Mat img1 = imread("saut/1.png");
    Mat img2 = imread("saut/2.png");
    Mat img3 = imread("saut/3.png");
    Mat img4 = imread("saut/4.png");
    Mat img5 = imread("saut/5.png");
    
    /*addWeighted(img1, 0.8, img2, 1.0, 0.0, img1);
    addWeighted(img1, 0.8, img3, 1.0, 0.0, img1);
    addWeighted(img1, 0.5, img4, 0.8, 0.0, img1);
    addWeighted(img1, 0.5, img5, 0.8, 0.0, img1);*/
    /*
    0-->500
    500-->950
    950-->1450
    1100-->1500
    */
    
    Mat dst(img1.size(), img1.type());
    copy_(dst, img1, 0, 500);
    //copy_(dst, img2, 500, 950);
    addWeighted(img3, 0.5, img4, 0.5, 0.0, img3);
    addWeighted(img3, 1, img2, 0.5, 0.0, img3);
    copy_(dst, img3, 500, img1.cols);
    //copy_(dst, img4, 1200, img1.cols);
    
    imshow("combine", dst);
    waitKey(0);
    return 0;
}