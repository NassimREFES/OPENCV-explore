#include <iostream>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv/cv.hpp>

using namespace cv;
using namespace std;

//typedef unsigned char uchar;

//Scan Image And Reduce C
Mat& siarc(Mat& I, const uchar* const table)
{
    CV_Assert(I.depth()==CV_8U);

    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols*channels;

    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    /*int i, j;
    uchar* p;
    for (i = 0; i < nRows; ++i) {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j) {
            p[j] = table[p[j]];
        }
    }*/


    uchar* p = I.data;
    for (unsigned int i = 0; i < nCols*nRows; i+=3) {
        *(p) = table[*(p)];
        *(p+1) = table[*(p+1)];
        *(p+2) = table[*(p+2)];
        p = p + 3;
    }

    return I;
}

Mat& siarc2(Mat& I, const uchar* const table)
{
    CV_Assert(I.depth()==CV_8U);
    uchar* p = I.data;
    const uchar* end   = I.dataend;

    while (p != end) {
        *(p) = table[*(p)];
        *(p+1) = table[*(p+1)];
        *(p+2) = table[*(p+2)];
        p = p + 3;
    }

    return I;
}

// scan image and reduce iterator
Mat& simari(Mat& I, const uchar* const table)
{
    CV_Assert(I.depth()==CV_8U);

    const int channels = I.channels();

    switch (channels) {
        case 1 :
        {
            MatIterator_<uchar> it, end;
            for (it=I.begin<uchar>(), end=I.end<uchar>(); it != end; ++it) {
                    *it = table[*it];
            }
            break;
        }
        case 3 :
        {
            MatIterator_<Vec3b> it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}

// scan image and reduce random access
Mat& siarra(Mat& I, const uchar* const table)
{
    CV_Assert(I.depth()==CV_8U);

    const int channels = I.channels();
    switch(channels) {
        case 1 :
        {
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j)
                    I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
            break;
        }
        case 3 :
        {
            Mat_<Vec3b> _I = I;
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j) {
                    _I(i, j)[0] = table[_I(i, j)[0]];
                    _I(i, j)[1] = table[_I(i, j)[1]];
                    _I(i, j)[2] = table[_I(i, j)[2]];
                }
            I = _I;
            break;
        }
    }

    return I;
}

int main(int argc, char** argv)
{
    int divideWith = 150;

    uchar table[256];
    for (int i = 0; i < 256; ++i)
        table[i] = (uchar)(divideWith*(i/divideWith));

    namedWindow("img", WINDOW_AUTOSIZE);
    namedWindow("img1", WINDOW_AUTOSIZE);
    namedWindow("img2", WINDOW_AUTOSIZE);
    namedWindow("img3", WINDOW_AUTOSIZE);
    namedWindow("img4", WINDOW_AUTOSIZE);

    Mat img = imread("5.jpg", CV_LOAD_IMAGE_COLOR);
    imshow("img", img);

    Mat img1 = img.clone();
    Mat img11 = img.clone();
    Mat img2 = img.clone();
    Mat img3 = img.clone();
    Mat img4 = img.clone();

    double t = (double)getTickCount();
    siarc(img1, table);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout << "siarc Times =  " << t << "s\n";

    t = (double)getTickCount();
    siarc2(img11, table);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout << "siarc2 Times=  " << t << "s\n";

    t = (double)getTickCount();
    simari(img2, table);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout << "simari Times = " << t << "s\n";

    t = (double)getTickCount();
    siarra(img3, table);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout << "siarra Times = " << t << "s\n";

    imshow("img1", img1);
    imshow("img11", img11);
    imshow("img2", img2);
    imshow("img3", img3);

    //---------------------------------

    Mat J;
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for (int i = 0; i < 256; ++i)
        p[i] = table[i];

    t = (double)getTickCount();
    LUT(img4, lookUpTable, J);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout << "LUT Times = " << t << "s\n";

    imshow("img4", J);

    /* image 4k
    siarc Times  = 0.0323182s
    siarc2 Times = 0.0318735s
    simari Times = 0.229315s
    siarra Times = 0.233707s
    LUT Times    = 0.244921s
    */

    /* image 8k
    siarc Times  = 0.133688s
    siarc2 Times = 0.131955s
    simari Times = 0.950775s
    siarra Times = 0.969326s
    LUT Times    = 0.280556s
    */


    waitKey(0);
    return 0;
}
