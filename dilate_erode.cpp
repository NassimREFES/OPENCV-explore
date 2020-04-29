#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilatation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int erosion_iter = 0;
int dilatation_elem = 0;
int dilatation_size = 0;
const int max_elem = 2;
const int max_iter = 10;
const int max_kernel_size = 21;

void erosion(int, void*)
{
    int erosion_type;
    if (erosion_elem == 0) erosion_type = MORPH_RECT;
    else if (erosion_elem == 1) erosion_type = MORPH_CROSS;
    else if (erosion_elem == 2) erosion_type = MORPH_ELLIPSE;

    Mat element = getStructuringElement(erosion_type,
                    Size(2*erosion_size+1, 2*erosion_size+1),
                    Point(erosion_size, erosion_size));

    //Mat e = (Mat_<uchar>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);
    erode(src, erosion_dst, element);
    //dilate(erosion_dst, erosion_dst, element);
    while(erosion_iter) { erode(erosion_dst, erosion_dst, element); --erosion_iter; }
    imshow("Erosion Demo", erosion_dst);
}

void dilatation(int, void*)
{
    int dilatation_type;
    if (dilatation_elem == 0) dilatation_type = MORPH_RECT;
    else if (dilatation_elem == 1) dilatation_type = MORPH_CROSS;
    else if (dilatation_elem == 2) dilatation_type = MORPH_ELLIPSE;

    Mat element = getStructuringElement(dilatation_type,
                    Size(2*dilatation_size+1, 2*dilatation_size+1),
                    Point(dilatation_size, dilatation_size));
    dilate(src, dilatation_dst, element);
    imshow("Dilatation Demo", dilatation_dst);
}



int main(int argc, char** argv)
{
    src = imread(argv[1]);
    if (!src.data) return -1;

    namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);
    namedWindow("Dilatation Demo", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Dilatation Demo", src.cols, 0);

    createTrackbar("Element:\n0:Rect\n1:Cross\n2:Ellipse", "Erosion Demo",
                    &erosion_elem, max_elem, erosion);
    createTrackbar("Kernel size:\n2n+1", "Erosion Demo",
                    &erosion_size, max_kernel_size, erosion);
    createTrackbar("iteration:\nn", "Erosion Demo",
                    &erosion_iter, max_iter, erosion);

    createTrackbar("Element:\n0:Rect\n1:Cross\n2:Ellipse", "Dilatation Demo",
                    &dilatation_elem, max_elem, dilatation);
    createTrackbar("Kernel size:\n2n+1", "Dilatation Demo",
                    &dilatation_size, max_kernel_size, dilatation);

    erosion(0, 0);
    dilatation(0, 0);

    waitKey(0);
    return 0;
}
