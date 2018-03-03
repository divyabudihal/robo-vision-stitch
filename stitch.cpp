#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <string>

using namespace cv;
using namespace std;

void stream (VideoCapture& vid, string outputWindow)
{
    namedWindow(outputWindow, WINDOW_NORMAL);
    for(;;)
    {
        Mat frame;
        vid >> frame; // get a new frame from video
        //invert(frame);
        //cvtColor(frame, edges, CV_BGR2GRAY);
        // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        // Canny(edges, edges, 0, 30, 3);
        bitwise_not ( frame, frame);
        imshow(outputWindow, frame);
        if(waitKey(30) >= 0) break;
    }
    return;
}

int main(int, char**)
{
    string vid1Location = "./iris-tests/dynamic_test.mp4";
    string vid2Location = "./iris-tests/field_trees.avi";
    
    VideoCapture vid1(vid1Location); // open the first test file
    if(!vid1.isOpened())  // check if we succeeded
    { 
        cout << "Video 1 File could not be successfully opened" << endl;
        return -1;
    }

    VideoCapture vid2(vid2Location); // open the second test file
    if(!vid2.isOpened())  // check if we succeeded
    { 
        cout << "Video 2 File could not be successfully opened" << endl;
        return -1;
    }

    // thread out1 (stream, vid1, "Video 1 Output");     // spawn new thread that calls foo()
    // thread out2 (stream, vid2, "Video 2 Output");  // spawn new thread that calls bar(0)

    // cout << "Streaming of two videos now executing concurrently...\n";

    // // synchronize threads:
    // out1.join();                // pauses until first finishes
    // out2.join();               // pauses until second finishes

    // cout << "Streaming completed.\n";

    stream(vid1, "Video 1 Output");

    
    // for(;;)
    // {
    //     Mat frame;
    //     vid >> frame; // get a new frame from video
    //     //invert(frame);
    //     //cvtColor(frame, edges, CV_BGR2GRAY);
    //     // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //     // Canny(edges, edges, 0, 30, 3);
    //     bitwise_not ( frame, frame);
    //     imshow("Output Video", frame);
    //     if(waitKey(30) >= 0) break;
    // }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

