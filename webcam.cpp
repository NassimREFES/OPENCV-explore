#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        cout << "Capture could not be opened successfully\n";
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
    }
    
    return 0;
}