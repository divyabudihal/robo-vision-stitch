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
    while(1)
    {
        Mat frame;
        vid >> frame; // get a new frame from video
        if (frame.empty())
            break;
        bitwise_not ( frame, frame);
        imshow(outputWindow, frame);
        if(waitKey(30) >= 0) break;
    }
    return;
}

void outputVid (VideoCapture& vid, string outputWindow, string outputFile)
{
    // Default resolution of the frame is obtained.The default resolution is system dependent. 
    int frame_width = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
    int frame_height = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
    VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
    while(1)
    { 
    Mat frame; 
        
    // Capture frame-by-frame 
    vid >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
        break;
    bitwise_not ( frame, frame); // invert frame
    // Write the frame into the file 'outcpp.avi'
    vidOut.write(frame);

    // Display the resulting frame    
    imshow( outputWindow, frame );

    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
        break;
    }
}

int main(int, char**)
{
    string vid1Location = "./iris-tests/dynamic_test.mp4";
    string vid2Location = "./iris-tests/field_trees.avi";

    string vid1Output = "video1.avi";
    string vid2Output = "video2.avi";
    
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

    cout << "Initializing thread for Video 1..." << endl;
    thread out1 (outputVid, ref(vid1), "Video 1 Output", vid1Output);     // spawn new thread that calls foo()
    // cout << "Initializing thread for Video 2..." << endl;
    // thread out2 (stream, ref(vid2), "Video 2 Output");  // spawn new thread that calls bar(0)

    // cout << "Streaming of two videos now executing concurrently...\n";

    // // synchronize threads:
    cout << "Joining thread for Video 1..." << endl;
    out1.join();                // pauses until first finishes
    // cout << "Joining thread for Video 2..." << endl;
    // out2.join();               // pauses until second finishes

    // cout << "Streaming completed.\n";

    //stream(vid1, "Video 1 Output");

    
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
    destroyAllWindows();
    return 0;
}

