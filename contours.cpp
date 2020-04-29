#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat img;
vector<vector<Point>> contours;
vector<Vec4i> heirarchy;

int lvl = 0;

void on_trackbar(int, void*)
{
    if (contours.empty()) return;
    Mat img_show = img.clone();
    drawContours(img_show, contours, -1, Scalar(0, 0, 255), 3, 8, heirarchy, lvl);
    imshow("Contours", img_show);
}

int main()
{
    img = imread("feu.jpg");
    Mat img_b;
    cvtColor(img, img_b, CV_RGB2GRAY);
    
    Mat edges;
    Canny(img_b, edges, 50, 100);
    
    findContours(edges, contours, heirarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
    
    namedWindow("Contours");
    createTrackbar("levels", "Contours", &lvl, 15, on_trackbar);
    
    on_trackbar(0, 0);
    
    while (char(waitKey(1)) != 'q') { }
    return 0;
}