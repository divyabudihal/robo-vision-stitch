#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture vid("./iris-tests/dynamic_test.mp4"); // open the first test file
    if(!vid.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges", WINDOW_NORMAL);
    for(;;)
    {
        Mat frame;
        vid >> frame; // get a new frame from video
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

