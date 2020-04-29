#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

char source_window[] = "source image";
char warp_window[] = "warp";
char warp_rotate_window[] = "warp + rotate";

void transform_(const Mat& src, Mat& dst)
{
    // rotation + transalation
    dst = Mat::zeros(src.rows*3, src.cols*3, src.type());
    float mx[3][2] = {
        {cos(1.0472), 0.5*sin(1.0472)},
        {-sin(1.0472)*0.5, cos(1.0472)},
        {src.rows, src.cols}
    };
    cout << mx[0][0] << ' ' << mx[0][1] << ' ' << mx[2][0] << '\n'
        << mx[1][0] << ' ' << mx[1][1] << ' ' << mx[2][1] << '\n';
    for (int j = 0; j < src.rows; ++j) {
        for (int i = 0; i < src.cols; ++i) {
            float cp[2];
            cp[0] = (mx[0][0]*j + mx[0][1]*i)+mx[2][0];
            cp[1] = (mx[1][0]*j + mx[1][1]*i)+mx[2][1]*2;
            circle(dst, Point2f(cp[1], cp[0]), 1, src.at<uchar>(j, i));
        }

    }

    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    namedWindow(warp_window, CV_WINDOW_AUTOSIZE);

    imshow(source_window, src);
    imshow(warp_window, dst);

    waitKey(0);
}

int main(int argc, char** argv)
{
    Point2f srct[3];
    Point2f dstt[3];

    Mat rot_mat(2, 3, CV_32FC1);
    Mat warp_mat(2, 3, CV_32FC1);
    Mat src, warp_dst, warp_rotate_dst;

    src = imread(argv[1], 1);
    //cvtColor(src, src, CV_BGR2GRAY);

    //transform_(src, warp_dst);

    warp_dst = Mat::zeros(src.rows, src.cols, src.type());

    srct[0] = Point2f(0, 0);
    srct[1] = Point2f(src.cols-1, 0);
    srct[2] = Point2f(0, src.rows-1);

    dstt[0] = Point2f(src.cols*0.0, src.rows*0.33);
    dstt[2] = Point2f(src.cols*0.85, src.rows*0.25);
    dstt[1] = Point2f(src.cols*0.15, src.rows*0.7);

    circle(src, srct[0], 5, Scalar(0, 0, 255), -1, 8);
    circle(src, srct[1], 5, Scalar(0, 0, 255), -1, 8);
    circle(src, srct[2], 5, Scalar(0, 0, 255), -1, 8);

// distortion
    warp_mat = getAffineTransform(srct, dstt);
    cout << warp_mat << '\n';
    warpAffine(src, warp_dst, warp_mat, warp_dst.size());

    Point center = Point(warp_dst.cols/2, warp_dst.rows/2);
    double angle = -50;
    double scale = 0.6;

    rot_mat = getRotationMatrix2D(center, angle, scale);

    warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());

    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    namedWindow(warp_window, CV_WINDOW_AUTOSIZE);
    namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);

    imshow(source_window, src);
    imshow(warp_window, warp_dst);
    imshow(warp_rotate_window, warp_rotate_dst);

    waitKey(0);
    return 0;
}
