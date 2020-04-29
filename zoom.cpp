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

Mat src, dst, tmp;
char window_name[] = "Pyramids Demo";

int main(int argc, char** argv)
{
    src = imread(argv[1]);
    if (!src.data) return -1;

    tmp = src;
    dst = tmp;

    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    imshow(window_name, dst);

    while (true) {
        int c;
        c = waitKey(0);

        if ((char)c == 27) break;
        else if ((char)c == 'u') {
            pyrUp(tmp, dst, Size(tmp.cols*2, tmp.rows*2));
            cout << "Zoom In: Image x 2\n";
        }
        else if ((char)c == 'd') {
            pyrDown(tmp, dst, Size(tmp.cols/2, tmp.rows/2));
            cout << "Zoom Out: Image / x\n";
        }

        imshow(window_name, dst);
        tmp = dst;
    }

    return 0;
}
