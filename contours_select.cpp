#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat img_all_contours;
vector< vector<Point> > closed_contours;
vector<Vec4i> heirarchy;

vector< vector<Point> > make_contours_closed(vector< vector<Point> > contours)
{
    vector< vector<Point> > closed_contours;
    closed_contours.resize(contours.size());
    for (int i = 0; i < contours.size(); ++i)
        approxPolyDP(contours[i], closed_contours[i], 0.1, true);
        
    return closed_contours;
}

int smallest_contour(Point p, vector< vector<Point> > contours, vector<Vec4i> heirarchy)
{
    int idx = 0, prev_idx = -1;
    while (idx >= 0) {
        vector<Point> c = contours[idx];
        double d = pointPolygonTest(c, p, false);
        if (d>0) {
            prev_idx = idx;
            idx = heirarchy[idx][2];
        }
        else idx = heirarchy[idx][0];
    }
    
    return prev_idx;
}

void on_mouse(int event, int x, int y, int, void*)
{
    if (event != EVENT_LBUTTONDOWN) return;
    
    Point p(x, y);
    
    int contour_show_idx = smallest_contour(p, closed_contours, heirarchy);
    
    if (contour_show_idx < 0) {
        imshow("Contours", img_all_contours);
        return;
    }
    
    vector< vector<Point> > contour_show;
    contour_show.push_back(closed_contours[contour_show_idx]);
    
    if (!contour_show.empty()) {
        Mat img_show = img_all_contours.clone();
        drawContours(img_show, contour_show, -1, Scalar(0, 0, 255), 3);
        imshow("Contours", img_show);
    }
}

int main()
{
    Mat img = imread("feu.jpg");
    img_all_contours = img.clone();
    
    Mat img_b;
    cvtColor(img, img_b, CV_RGB2GRAY);
    
    Mat edges;
    Canny(img_b, edges, 50, 100);
    
    vector< vector<Point> > contours;
    findContours(edges, contours, heirarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
    
    closed_contours = make_contours_closed(contours);
    
    drawContours(img_all_contours, closed_contours, -1, Scalar(0, 255, 0));
    
    imshow("Contours", img_all_contours);
    
    setMouseCallback("Contours", on_mouse);
    
    while (char(waitKey(1)) != 'q') { }
    
    return 0;
}
