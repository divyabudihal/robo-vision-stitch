#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <string>
#include <queue>

using namespace cv;
using namespace std;


struct myMat
{
    cv::Mat frame; /// Standard cv::Mat
    string inputFile;
    myMat(){};   /// Default constructor
    ~myMat(){};  /// Destructor (called by queue::pop)
 
    /// Copy constructor (called by queue::push)
    myMat(const myMat& src)
    {
        src.frame.copyTo(frame);
    }
};


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
    int frameWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
    int frameHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 
    double frameRate = vid.get(CV_CAP_PROP_FPS);
    
    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
    VideoWriter vidOut(outputFile,CV_FOURCC('M','P','J','G'), 30, Size(frameWidth,frameHeight)); 
    
    while(1)
    { 
    Mat frame; 
        
    // Capture frame-by-frame 
    vid >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
        break;
    bitwise_not (frame, frame); // invert frame
    // Write the frame into the file 'outcpp.avi'
    vidOut.write(frame);

    //cout << "Writing to file " << outputFile << endl;
    // Display the resulting frame    
    imshow( outputWindow, frame );

    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
        break;
    }
}

void processVid(VideoCapture& vid, queue<myMat>& record, string vidInput)
{
    
    while(1)
    {
        Mat frame;
        vid >> frame; // get a new frame from video
        if (frame.empty())
            break;
        bitwise_not ( frame, frame);
        // imshow(outputWindow, frame);
        record.push(myMat()); // create a new empty mat
        frame.copyTo(record.front().frame);  // take a full copy
        record.front().inputFile = vidInput;
        cout << record.front().frame << endl;
        cout << record.front().inputFile << endl;
        // cout << "Reading from " << vidInput << endl;
        if(waitKey(30) >= 0) break;
    }
    return;
}



void createVid( VideoCapture& vid, queue<myMat>& record, string outputFile)
{
    int frameWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
    int frameHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 
    double frameRate = vid.get(CV_CAP_PROP_FPS);
    
    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
    VideoWriter vidOut(outputFile,CV_FOURCC('M','P','J','G'), 10, Size(frameWidth,frameHeight)); 
    Mat currFrame;
    cout << "Starting to create video ..." << endl;
    while (!record.empty())
    {
        cout << "Writing to " << outputFile << endl;
        currFrame = record.front().frame;
        vidOut.write(currFrame);
        record.pop();
        if(waitKey(10) >= 0) break;
    }

}

int main(int, char**)
{
    // int frameHeight;
    // int frameWidth;
    // int frameRate;
    
    string vid1Location = "./test1.mp4";
    string vid2Location = "./iris-tests/field_trees.avi";

    string vid1Input = "test1.mp4";
    string vid2Input = "field_trees.avi";

    string vid1Output = "video1.avi";
    string vid2Output = "video2.avi";

    queue<myMat> vid1Queue;
    queue<myMat> vid2Queue;
    
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
    // thread out1 (outputVid, ref(vid1), "Video 1 Output", vid1Output);     // spawn new thread that calls foo()
    thread out1 (processVid, ref(vid1), ref(vid1Queue), vid1Input);     // spawn new thread that calls foo()
    cout << "Initializing thread for Video 2..." << endl;
    thread out2 (processVid, ref(vid2), ref(vid2Queue), vid2Input);  // spawn new thread that calls bar(0)

    thread::id id1 = out1.get_id();
    thread::id id2 = out2.get_id();
    // cout << "Streaming of two videos now executing concurrently...\n";

    // // synchronize threads:
    if (out1.joinable())
    {
        cout << "Joining thread for Video 1, ID = " << id1 << endl;
        out1.join();                // pauses until first finishes
    }
    
   
    if (out2.joinable())
    {
        cout << "Joining thread for Video 2, ID = " << id2 << endl;
        out2.join();               // pauses until second finishes
    }

    createVid( vid1, vid1Queue, vid1Output);

    // the camera will be deinitialized automatically in VideoCapture destructor
    destroyAllWindows();
    return 0;
}

