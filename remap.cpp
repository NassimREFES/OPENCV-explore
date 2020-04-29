#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat src, dst;
Mat map_x, map_y;
char rempa_window[] = "remap demo";
int ind = 0;

void update_map(void)
{
    ind = ind%4;
    for (int j = 0; j < src.rows; ++j) {
        for (int i = 0; i < src.cols; ++i) {
            switch(ind) {
                case 0:
                    if (i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75) {
                        map_x.at<float>(j, i) = 2*(i-src.cols*0.25)+0.5;
                        map_y.at<float>(j, i) = 2*(j-src.cols*0.25)+0.5;
                    }
                    else {
                        map_x.at<float>(j, i) = 0;
                        map_y.at<float>(j, i) = 0;
                    }
                    break;
                case 1:
                    map_x.at<float>(j, i) = i;
                    map_y.at<float>(j, i) = src.rows-j;
                    break;
                case 2:
                    map_x.at<float>(j, i) = src.cols - i;
                    map_y.at<float>(j, i) = j;
                    break;
                case 3:
                    map_x.at<float>(j, i) = src.cols - i;
                    map_y.at<float>(j, i) = src.rows - j;
                    break;
            }
        }
    }
}

int main(int argc, char** argv)
{
    src = imread(argv[1], 1);

    dst.create(src.size(), src.type());
    map_x.create(src.size(), CV_32FC1);
    map_y.create(src.size(), CV_32FC1);

    namedWindow(rempa_window, CV_WINDOW_AUTOSIZE);

    while (true) {
        int c = waitKey(1000);
        if ((char)c == 27) break;

        update_map();

        remap(src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

        imshow(rempa_window, dst);

        ++ind;
    }
    return 0;
}
