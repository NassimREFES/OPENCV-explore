#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void blending(const Mat& mx1, double alpha, const Mat& mx2,
              double beta, double gamma, Mat& dest_mx)
{
    CV_Assert(mx1.depth()==CV_8U && mx2.depth()==CV_8U &&
              mx1.rows == mx2.rows && mx1.cols == mx2.cols);
    dest_mx.create(mx1.size(), mx1.type());

    const uchar* pmx1 = mx1.data;
    const uchar* pmx2 = mx2.data;
    uchar* pdest_mx = dest_mx.data;
    const uchar* pdest_mx_end = dest_mx.dataend;

    while (pdest_mx != pdest_mx_end)
        *pdest_mx++ = fmod(((*pmx1++)*alpha + (*pmx2++)*beta + gamma),256);
}

int main()
{
    double alpha = 0.8;
    double beta;

    Mat src1, src2, dst;

    src1 = imread("LinuxLogo.jpg");
    src2 = imread("WindowsLogo.jpg");

    namedWindow("Linear Blend", 1);

    beta = 1 - alpha;

    //addWeighted(src1, alpha, src2, beta, 0.0, dst);
    blending(src1, alpha, src2, beta, 0.0, dst);

    imshow("Linear Blend", dst);

    waitKey(0);
    return 0;
}
