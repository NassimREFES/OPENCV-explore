#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src, dst;

    char src_win[] = "source image";
    char equalize_win[] = "equalized image";

    src = imread(argv[1], 1);

    if (!src.data) return -1;

    cvtColor(src, src, CV_BGR2GRAY);

    equalizeHist(src, dst);

    namedWindow(src_win, CV_WINDOW_AUTOSIZE);
    namedWindow(equalize_win, CV_WINDOW_AUTOSIZE);

    imshow(src_win, src);
    imshow(equalize_win, dst);

    Mat dstt;
    equalizeHist(dst, dstt);
    imshow("lol", dstt);

    waitKey(0);
    return 0;
}
