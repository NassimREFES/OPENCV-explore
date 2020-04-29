#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src, srcg;

    src = imread(argv[1], 1);

    if (!src.data) return -1;

    cvtColor(src, srcg, CV_BGR2GRAY);

    GaussianBlur(srcg, srcg, Size(9, 9), 2, 2);

    vector<Vec3f> circles;

    HoughCircles(srcg, circles, CV_HOUGH_GRADIENT, 1, srcg.rows/64, 1, 70, 0, 0);

    for (size_t i = 0; i < circles.size(); ++i) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        circle(src, center, 3, Scalar(255, 255, 0), -1, 8, 0);
        circle(src, center, radius, Scalar(255, 0, 255), 3, 8, 0);
    }
    cout << circles.size() << '\n';
    namedWindow("hough", CV_WINDOW_AUTOSIZE);
    imshow("hough", src);
    waitKey(0);
    return 0;
}
