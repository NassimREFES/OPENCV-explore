#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdio>
#include <cstdlib>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src, src_gray, dst;
    Mat grad;
    char window_name[] = "sobel demo - simple edge detector";
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    int c;

    src = imread(argv[1]);

    if (!src.data) return -1;

    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

    cvtColor(src, src_gray, CV_BGR2GRAY);
    

    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;


    /*Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);*/
    /*Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
    Scharr(src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);*/
    /*Mat Gx = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat Gy = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    filter2D(src_gray, grad_x, ddepth, Gx, Point(-1, -1), delta, BORDER_DEFAULT);
    filter2D(src_gray, grad_y, ddepth, Gy, Point(-1, -1), delta, BORDER_DEFAULT);*/
    /*convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);*/

    Laplacian(src_gray, dst, ddepth, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(dst, grad);
    
    uchar* p = grad.data;
    const uchar* e = grad.dataend;
    while (p != e) {
        *p = (255-*p);
        ++p;
    }

    imshow(window_name, grad);
    waitKey(0);
    return 0;
}
