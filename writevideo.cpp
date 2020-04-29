#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    
    Size s = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), 
        (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    VideoWriter put("output.mpg", CV_FOURCC('M', 'P', 'E', 'G'), 10, s);
    if (!put.isOpened()) {
        cout << "File could not be created for writting. check permissions\n";
        return -1;
    }
    namedWindow("Video");
    while (char(waitKey(1)) != 'q' && cap.isOpened()) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cout << "Video over\n";
            break;
        }
        imshow("Video", frame);
        put << frame;
    }
    
    return 0;
}