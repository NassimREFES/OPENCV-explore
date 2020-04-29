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

Mat src, dst;
int top_, bottom_, left_, right_;
int borderType;
Scalar value;
char window_name[] = "copyMakeBorder Demo";
RNG rng(12345);

int main(int argc, char** argv)
{
    int c;
    src = imread(argv[1]);

    if (!src.data) return -1;

    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    top_ = bottom_ = (int)(0.5*src.rows);
    left_ = right_ = (int)(0.5*src.cols);

    dst=src;

    imshow(window_name, dst);

    while(true) {
        c = waitKey(500);
        if ((char)c == 27) break;
        else if((char)c == 'c') borderType = BORDER_CONSTANT;
        else if ((char)c == 'r') borderType = BORDER_REPLICATE;

        value = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst, top_, bottom_, left_, right_, borderType, value);
        imshow(window_name, dst);
    }
    return 0;
}
