#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

 int main()
 {
     Mat atom_image = Mat::zeros(400, 400, CV_8UC3);
     Mat rook_image = Mat::zeros(400, 400, CV_8UC3);

     int thickness = 2;
     int lineType  = 8;

     ellipse(atom_image, Point(200, 200), Size(100, 25), 90,
             0, 360, Scalar(255, 0, 0), thickness, lineType);
    ellipse(atom_image, Point(200, 200), Size(100, 25), 0,
             0, 360, Scalar(255, 0, 0), thickness, lineType);
     ellipse(atom_image, Point(200, 200), Size(100, 25), 45,
             0, 360, Scalar(255, 0, 0), thickness, lineType);
     ellipse(atom_image, Point(200, 200), Size(100, 25), -45,
             0, 360, Scalar(255, 0, 0), thickness, lineType);
     circle(atom_image, Point(200, 200), 12.5, Scalar(0, 0, 255),
            -1, lineType);

        Point rook_points[1][20];
        int w = 400;
        rook_points[0][0]  = Point(    w/4,   7*w/8 );
        rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
        rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
        rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
        rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
        rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
        rook_points[0][6]  = Point(  3*w/4,     w/8 );
        rook_points[0][7]  = Point( 26*w/40,    w/8 );
        rook_points[0][8]  = Point( 26*w/40,    w/4 );
        rook_points[0][9]  = Point( 22*w/40,    w/4 );
        rook_points[0][10] = Point( 22*w/40,    w/8 );
        rook_points[0][11] = Point( 18*w/40,    w/8 );
        rook_points[0][12] = Point( 18*w/40,    w/4 );
        rook_points[0][13] = Point( 14*w/40,    w/4 );
        rook_points[0][14] = Point( 14*w/40,    w/8 );
        rook_points[0][15] = Point(    w/4,     w/8 );
        rook_points[0][16] = Point(    w/4,   3*w/8 );
        rook_points[0][17] = Point( 13*w/32,  3*w/8 );
        rook_points[0][18] = Point(  5*w/16, 13*w/16 );
        rook_points[0][19] = Point(    w/4,  13*w/16 );

    const Point* ppt[1] = {rook_points[0]};
    int npt[] = { 20 };

    fillPoly(atom_image, ppt, npt, 1, Scalar(255, 255, 255), lineType);

// Point
/*  --------------->(x)
   |
   |
   |
   |
   (y)
*/
    line(atom_image, Point(50, 300), Point(300, 300), Scalar(0, 255, 0),
        thickness, lineType);

    putText(atom_image, "Oh Yeah openCV !!!", Point(50, 370), 1, 1,
            Scalar(0, 255, 255));

    // random generator
    RNG rng;
    cout << rng.uniform(1, 10) << '\n';
    rng.next();
    cout << rng.uniform(1, 10) << '\n';

    imshow("atom_image", atom_image);
    waitKey(0);
    return 0;
 }
