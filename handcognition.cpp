#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

Mat src, src_gray, dst, cnt;
vector< vector<Point> > contours;
vector< vector<Point> > envelope_convex;
vector< vector<int> > i_envelope_convex;
vector< vector<Vec4i> > def_convex;
vector< Vec4i > hierarchie;
char dstt[] = "dst";
int nombre_doigt = 0;

void cb_trackbar_threshold(int, void*)
{

}

int main(int argc, char** argv)
{
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    namedWindow("srcc", CV_WINDOW_AUTOSIZE);
    namedWindow(dstt, CV_WINDOW_AUTOSIZE);

    VideoCapture cam(0);
    if (!cam.isOpened()) return -1;
while (true) {
    //src = imread(argv[1], 1);
    cam >> src;
    cnt = Mat(src.size(), src.type());
    if (!src.data) return -1;
    //GaussianBlur(src, src, Size(9, 9), 2, 2);
    cvtColor(src, src_gray, CV_BGR2GRAY);

    /*createTrackbar("Value: ", dstt, &seuil, 255, cb_trackbar_threshold);
    cb_trackbar_threshold(0, 0);*/

    Mat srcc = src.clone();
    threshold(src_gray, dst, 0, 255, THRESH_OTSU);
    findContours(dst, contours, hierarchie, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    // pour chaque contour, trouvé l'envelope convex
    //envelope_convex.clear();
    envelope_convex.resize(contours.size());
    //i_envelope_convex.clear();
    i_envelope_convex.resize(contours.size());
    int max_sz = contours[0].size();
    int max_i  = 0;
    for (int i = 1; i < contours.size(); ++i)
        if (max_sz < contours[i].size()) {
            max_sz = contours[i].size();
            max_i = i;
        }

    cout << max_i << " " << max_sz << '\n';

    for( int i = 0; i < contours.size(); ++i ) {
        if (i == max_i) {
            convexHull( Mat(contours[i]), envelope_convex[i], false );
            convexHull( Mat(contours[i]), i_envelope_convex[i], false );
            /*i_envelope_convex[i].resize(contours[i].size());
            cout << envelope_convex[i].size() << " " << contours[i].size() << '\n';
            convexityDefects( i_envelope_convex[i], envelope_convex[i], def_convex );*/
        }
    }

    def_convex.clear();
    def_convex.resize(contours.size());
    //def_convex[max_i].resize(contours[max_i].size());
    cout << i_envelope_convex.size() << " " << contours.size() << '\n';
    for( int i = 0; i < contours.size(); ++i ) {
        if (i == max_i) {
            cout << "--- "  << i << '\n';
            def_convex[i].resize(contours[i].size());
        convexityDefects( Mat(contours[i]), Mat(i_envelope_convex[i]), def_convex[i] );
        }
    }

    //cout << def_convex[5].size() << '\n';
    // hierarchie de tout les contours trouvé
    /*int idx = 0;
    for( ; idx >= 0; idx = hierarchie[idx][0] )
    {
        if (idx == max_i) {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours(srcc, contours, idx, color);
        drawContours(srcc, envelope_convex, idx, color);
        drawContours(dst, contours, idx, Scalar(255, 255, 255));
        drawContours(dst, envelope_convex, idx, Scalar(255, 255, 255));
    }
}*/

    drawContours(srcc, contours, max_i, Scalar(255, 0, 0));
    drawContours(srcc, envelope_convex, max_i, Scalar(0, 255, 0));
    drawContours(dst, contours, max_i, Scalar(255, 255, 255));
    drawContours(dst, envelope_convex, max_i, Scalar(255, 255, 255));
double count = 0;
        for (int j = 1; j < def_convex[max_i].size(); ++j) {
            //cout << j << '\n';
            /*circle(srcc, contours[max_i][def_convex[max_i][j][3]/256],
                4, Scalar(255, 200, 200));*/
            Point a = contours[max_i][def_convex[max_i][j][2]];
            Point b = contours[max_i][def_convex[max_i][j-1][2]];
            double dist = sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
            cout << dist << '\n';
            if (dist > 20) {
                ++count;
                circle(srcc, contours[max_i][def_convex[max_i][j][2]],
                    4, Scalar(255, 0, 255));
            line(srcc, contours[max_i][def_convex[max_i][j][2]],
                contours[max_i][def_convex[max_i][j-1][1]],
                Scalar(255, 255, 255));
            line(srcc, contours[max_i][def_convex[max_i][j][2]],
                contours[max_i][def_convex[max_i][j][1]],
                Scalar(255, 255, 255));
            }
            a = contours[max_i][def_convex[max_i][j][1]];
            b = contours[max_i][def_convex[max_i][j-1][1]];
            dist = sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
            if (dist > 20)
                circle(srcc, contours[max_i][def_convex[max_i][j][1]],
                    4, Scalar(0, 0, 255));

            /*circle(srcc, contours[max_i][def_convex[max_i][j][0]],
                4, Scalar(0, 255, 0));*/
        }
        /*circle(srcc, contours[max_i][def_convex[max_i][0][0]],
            4, Scalar(0, 0, 255));
        circle(srcc, contours[max_i][def_convex[max_i][1][1]],
            4, Scalar(0, 0, 255));
        circle(srcc, contours[max_i][def_convex[max_i][2][0]],
            4, Scalar(0, 0, 255));*/

    // trop sensible au mouvement
    // doit relier convexhull a defect convex
    String s = "";
    count = count;
    cout << "--> " << count << '\n';
    if (10 <= count) // max
        s += '5';
    else if (count < 10 && 8 <= count)
        s += '4';
    else if (count < 8 && 6 <= count)
        s += '3';
    else if (count < 6 && 4 <= count)
        s += '2';
    else if (count < 4)
        s += '1';
    else // min
        s += '0';

    putText(srcc, s, Point(50, 80), FONT_HERSHEY_COMPLEX_SMALL, 4, Scalar(255, 0, 0));
    imshow(dstt, dst);
    imshow("srcc", srcc);


    imshow("src", src);

    if (waitKey(30)>=0) break;

}

waitKey(0);
    return 0;
}
