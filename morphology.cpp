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

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
const int max_operator = 4;
const int max_elem = 2;
const int max_kernel_size = 21;

char window_name[] = "Morphology transformations demo";

void morphology_operations(int, void*)
{
    int operations = morph_operator + 2;

    Mat element = getStructuringElement(morph_elem,
                    Size(2*morph_size+1, 2*morph_size+1),
                    Point(morph_size, morph_size));

    morphologyEx(src, dst, operations, element);
    imshow(window_name, dst);
}

int main(int argc, char** argv)
{
    src = imread(argv[1]);

    if (!src.data) return -1;

    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    createTrackbar("Operation:\n0:Opening - 1:Closing\n2:Gradient - 3:Top Hat\n4:Black hat",
                    window_name, &morph_operator, max_operator, morphology_operations);
    createTrackbar("Element:\n0:Rect - 1:Cross - 2:Ellipse", window_name, &morph_elem,
                    max_elem, morphology_operations);
    createTrackbar("Kernel size:\n2n + 1", window_name, &morph_size,
                    max_kernel_size, morphology_operations);
    morphology_operations(0, 0);
    waitKey(0);
    return 0;
}
