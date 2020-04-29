#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    //Mat img = imread("alphabet.jpg", 0);
    Mat img = imread(argv[1], 0);
    Mat imgs = img.clone();
    GaussianBlur( img, img, Size( 11, 11 ), 0, 0 );
    img = Scalar::all(255) - img;
    threshold(img, img, 0, 255, THRESH_OTSU);
    Mat skel(img.size(), CV_8UC1, Scalar(0));
    Mat temp(img.size(), CV_8UC1);
    Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
    bool done;
    do {
        /*
        skel |= (img & !open(img))
        img = erosion(img)
        */
        morphologyEx(img, temp, MORPH_OPEN, element);
        bitwise_not(temp, temp);
        bitwise_and(img, temp, temp);
        bitwise_or(skel, temp, skel);
        erode(img, img, element);
        
        double max;
        minMaxLoc(img, 0, &max);
        done = (max==0);
    } while (!done);
    
    //for_each(skel.begin(), skel.end(), [](uchar* x) {if (*x) *x = })
    addWeighted(skel, 1.0, imgs, 0.5, 0.0, imgs);
    imshow("skeleton", imgs);
    waitKey(0);
    return 0;
}