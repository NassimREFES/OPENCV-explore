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

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
const int max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char window_name[] = "Edge Map";

void cannyThreshold(int, void*)
{
    blur(src_gray, detected_edges, Size(3, 3));

    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

    dst = Scalar::all(0);

    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

int main(int argc, char** argv)
{
    src = imread(argv[1]);

    if (!src.data) return -1;

    dst.create(src.size(), src.type());

    cvtColor(src, src_gray, CV_BGR2GRAY);

    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    createTrackbar("MinThreshold:", window_name, &lowThreshold, max_lowThreshold, cannyThreshold);

    cannyThreshold(0, 0);

    waitKey(0);

    return 0;
}
