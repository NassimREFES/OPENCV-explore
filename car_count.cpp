#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{
    Mat src, modified, temp, temp2;
    bool run = false;
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    namedWindow("modified", CV_WINDOW_AUTOSIZE);
    
    String name_video = "test3.mp4";
    VideoCapture video_(name_video);
    if (!video_.isOpened()) return -1;
    while (true) {
        video_ >> src;
        temp2 = src.clone();
        modified.deallocate();
        if (run) {
            cvtColor(src, src, CV_BGR2HSV);
            GaussianBlur(src, src, Size(11, 11),0, 0);
            threshold(src, src, 0, 255, THRESH_OTSU);
            
            modified = Mat::zeros(src.size(), src.type());
            
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    if (src.at<uchar>(i, j) != temp.at<uchar>(i, j))
                        modified.at<uchar>(i, j) = 255;
                }
            }
            
            //medianBlur(modified, modified, 3);
            
            
            /*for (int i = 1; i < modified.rows-1; ++i) {
                for (int j = 1; j < modified.cols-1; ++j) {
                    if (modified.at<uchar>(i, j)) {
                        int sum = modified.at<uchar>(i-1, j) + modified.at<uchar>(i, j-1) + 
                                    modified.at<uchar>(i-1, j-1) + modified.at<uchar>(i+1, j) + 
                                    modified.at<uchar>(i, j+1) + modified.at<uchar>(i+1, j+1) + 
                                    modified.at<uchar>(i+1, j-1) + modified.at<uchar>(i-1, j+1);
                        if (sum <1020)
                            modified.at<uchar>(i, j) = 0;
                    }
                }
            }*/
            
            /*Mat_<Vec3b> _src = src;
            Mat_<Vec3b> _temp = temp;
            Mat_<Vec3b> _modified = modified;
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    if (_src(i, j)[0] != _temp(i, j)[0] && _src(i, j)[1] != _temp(i, j)[1] && 
                        _src(i, j)[2] != _temp(i, j)[2]) {
                            _modified(i, j)[0] =  _modified(i, j)[1] = _modified(i, j)[2] = 255;
                        }
                 }
            }*/
        }
        
        imshow("src", src);
        if (run) imshow("modified", modified);
        temp = src.clone();
        run = true;
        if (waitKey(30)>=0) break;
    }
    
    return 0;
}