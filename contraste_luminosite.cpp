#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void contraste_luminosite(const Mat& src, double alpha, double beta, Mat& dst)
{
    CV_Assert(src.depth() == CV_8U);
    dst = Mat::zeros(src.size(), src.type());
    const int channels = src.channels();

    for (int x = 0; x < src.rows; ++x)
        for (int y = 0; y < src.cols; ++y)
            for (int c = 0; c < channels; ++c) {
                dst.at<Vec3b>(x, y)[c] = saturate_cast<uchar>(
                    alpha*src.at<Vec3b>(x, y)[c]+beta
                );
            }
}

int main()
{
    try {
    Mat img = imread("n3.jpg");
    Mat res;
    IplImage* iii = &img.operator IplImage();
    namedWindow("resultat");
    //img.convertTo(res, -1, 2.2, 50);
    contraste_luminosite(img, 2.2, 50, res);
    imshow("resultat", res);
    waitKey(0);
} catch(cv::Exception e) {
    cerr << e.what() << '\n';
}
    return 0;
}
