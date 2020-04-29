#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

bool ldown = false, lup = false;

Mat img;

Point corner1, corner2;

Rect box;

static void mouse_callback(int event, int x, int y, int, void*)
{
    if (event == EVENT_LBUTTONDOWN) {
        ldown = true;
        corner1.x = x;
        corner1.y = y;
        cout << "Corner 1 recorded at " << corner1 << endl;
    }
    if (event == EVENT_LBUTTONUP) {
        if (abs(x-corner1.x) > 20 && abs(y-corner1.y) > 20) {
            lup = true;
            corner2.x = x;
            corner2.y = y;
            cout << "Corner 2 recorded at " << corner2 << "\n\n";
        }
        else {
            cout << "Please select a bigger region" << '\n';
            ldown = false;      
        }
    }
    
    if (ldown && !lup) {
        Point pt;
        pt.x = x;
        pt.y = y;
        Mat local_img = img.clone();
        rectangle(local_img, corner1, pt, Scalar(0, 0, 255));
        imshow("Cropping app", local_img);
    }
    if (ldown && lup) {
        box.width = abs(corner1.x-corner2.x);
        box.height = abs(corner1.y-corner2.y);
        box.x = min(corner1.x, corner2.x);
        box.y = min(corner1.y, corner2.y);
        
        Mat crop(img, box);
        namedWindow("Crop");
        imshow("Crop", crop);
        
        ldown = lup = false;
    }
}

int main()
{
    img = imread("char10.jpg");
    namedWindow("Cropping app");
    imshow("Cropping app", img);
    setMouseCallback("Cropping app", mouse_callback);
    
    while (char(waitKey(1)) != 'q') { }
    return 0;
}