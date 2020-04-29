#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
Mat src, hsv, hue;
int bins = 10;

struct B 
{
    
};

class C
{

};

void hist_and_backproj(int, void*)
{
    MatND hist;
    int histSize = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float* ranges = {hue_range};
    calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

    MatND backproj;
    calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);

    imshow("BackProj", backproj);

    int w = 400;
    int h = 400;
    int bin_w = cvRound((double)w/histSize);
    Mat histimg = Mat::zeros(w, h, CV_8UC3);

    for (int i = 0; i < bins; ++i) {
        rectangle(histimg, Point(i*bin_w, h),
                    Point((i+1)*bin_w, h-cvRound(hist.at<float>(i)*h/255.0)),
                    Scalar(0, 0, 255), -1);
    }
    imshow("histograme", histimg);
}

int main(int argc, char** argv)
{
    src = imread(argv[1], 1);
    cvtColor(src, hsv, CV_BGR2HSV);
    hue.create(hsv.size(), hsv.depth());
    int ch[] = {0, 0};
    mixChannels(&hsv, 1, &hue, 1, ch, 1);

    char window_image[] = "source image";
    namedWindow(window_image, CV_WINDOW_AUTOSIZE);
    createTrackbar("* Hue bins: ", window_image, &bins, 180, hist_and_backproj);
    hist_and_backproj(0, 0);

    imshow(window_image, src);
    waitKey(0);
    return 0;
}
