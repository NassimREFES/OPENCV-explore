

int threshold_value = 0;
int threshold_type = 3;
const int max_value = 255;
const int max_type = 4;
const int max_binary_value = 255;

Mat src, src_gray, dst;
char window_name[] = "Threshold Demo";

char trackbar_type[] = "Type:\n0:binary\n1:binary inverted\n2:truncate\n3:to zero\n to zero inverted";
char trackbar_value[] = "Value";

void threshold_demo(int, void*)
{
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    imshow(window_name, dst);
}

int main(int argc, char** argv)
{
    src = imread(argv[1]);

    cvtColor(src, src_gray, CV_BGR2GRAY);
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    createTrackbar(trackbar_type, window_name, &threshold_type, max_type, threshold_demo);
    createTrackbar(trackbar_value, window_name, &threshold_value, max_value, threshold_demo);

    threshold_demo(0, 0);

    while (true) {
        int c = waitKey(20);
        if ((char)c == 27) break;
    }

    return 0;
}
