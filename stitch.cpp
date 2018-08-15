/*!
 * @file stitch.cpp
 * @brief Application used to invert and stitch two videos together frame by frame.
 * Two videos are read simulataneously and the output video is a video with alternating frames from each video.
 * @author D. Budihal
 * @date 3/10/2018
 */

#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <string>

using namespace cv;
using namespace std;

#define OUTPUT_FPS 30

bool readersDone = false;

void outputVid ( Mat& readerMat1, Mat& readerMat2, bool& reader1, bool& reader2, string outputWindow, string outputFile, int frameHeight, int frameWidth)
{

    cout << "Starting to write to file..." << endl;
    VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),OUTPUT_FPS, Size(frameWidth,frameHeight)); // create vidOut object
    while(1)
    { 
    
    if (readersDone == true) // if a reader is done, break out of the writing loop
        break;
   
    while (reader1 == false && readersDone == false)
    {
        // waiting for next Reader 1 frame...
    } //wait

    if (reader1 == true && readersDone == false)
    {
        reader1 = false; // set reader to false -> new read data needed
        if (readerMat1.empty()) // break if frame is empty
            break;

        resize(readerMat1,readerMat1,Size(frameWidth, frameHeight)); // resize frame
        vidOut.write(readerMat1); // write frame to video
        // imshow( outputWindow, readerMat1 ); // display resulting frame
    }


    while (reader2 == false && readersDone == false)
    {
        // waiting for next Reader 2 frame...
    }  // waits

    if (reader2 == true && readersDone == false)
    {
        reader2 = false;

        if (readerMat2.empty()) // break if frame is empty
            break;

        resize(readerMat2,readerMat2,Size(frameWidth, frameHeight)); // resize frame
        vidOut.write(readerMat2); // write frame to video
        // imshow( outputWindow, readerMat2 ); // display the resulting frame 
    }
        

    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
        break;
    }

    cout << "Finished writing to output file." << endl;
}


void reader (VideoCapture& vid, Mat& readerMat, bool& reader, string vidInput)
{
    cout << vidInput << " Reader Active" << endl;
    while(1)
    { 

    if (readersDone == true)
    {
        reader = false;
        break; // stop reading because one of the videos is over
    }
   
    while (reader != false && readersDone == false)
    {
       // wait until writer needs a new value
    }
    vid >> readerMat;
    bitwise_not ( readerMat, readerMat); // invert readerMat
    
    if (readerMat.empty())
        break; // stop reading because the current video is over

    reader = true; // indicate that this reader's value is ready to be writter
    
    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
        break;
    
    }
    cout << "Reader is done capturing frames from " << vidInput << endl;
    readersDone = true; // set readersDone flag to true because reader has finished 
    return;
}

int stitch (string vid1Input, string vid2Input, string vidOutput)
{
int frameHeight;
    int frameWidth;

    Mat readerMat1;
    Mat readerMat2;

    // set reader flags to false initially

    bool reader1Flag = false;
    bool reader2Flag = false;
    
    VideoCapture vid1(vid1Input); // open the first test file
    if(!vid1.isOpened())  // check if we succeeded
    { 
        cout << "Video 1 File could not be successfully opened" << endl; // print error and exit
        return -1;
    }

    VideoCapture vid2(vid2Input); // open the second test file
    if(!vid2.isOpened())  // check if we succeeded
    { 
        cout << "Video 2 File could not be successfully opened" << endl; // print error and exit
        return -1;
    }

    // print FPS values of input videos
    cout << "Video 1 FPS: " << vid1.get(CV_CAP_PROP_FPS) << endl;
    cout << "Video 2 FPS: " << vid2.get(CV_CAP_PROP_FPS) << endl;

    // choose frame height and frame width corresponding to the smallest dimensions present in both videos
    
    // choose smallest frame height
    if (vid1.get(CV_CAP_PROP_FRAME_HEIGHT) <= vid2.get(CV_CAP_PROP_FRAME_HEIGHT))
    {
        frameHeight = vid1.get(CV_CAP_PROP_FRAME_HEIGHT);
    }
    else
    {
        frameHeight = vid2.get(CV_CAP_PROP_FRAME_HEIGHT);
    }

    // choose smallest frame width
    if (vid1.get(CV_CAP_PROP_FRAME_WIDTH) <= vid2.get(CV_CAP_PROP_FRAME_WIDTH))
    {
        frameWidth = vid1.get(CV_CAP_PROP_FRAME_WIDTH);
        // vid2.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
    }
    else
    {
        frameWidth = vid2.get(CV_CAP_PROP_FRAME_WIDTH);
        // vid1.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
    }

    
    cout << "Output Frame Width: " << frameWidth << endl;
    cout << "Output Frame Height: " << frameHeight << endl;
    
    
    cout << "Initializing thread for Video 1..." << endl;
    thread read1 (reader, ref(vid1), ref(readerMat1), ref(reader1Flag), vid1Input);     // spawn new thread that calls reader with Video 1 info
    cout << "Initializing thread for Video 2..." << endl;
    thread read2 (reader, ref(vid2), ref(readerMat2), ref(reader2Flag), vid2Input);  // spawn new thread that calls reader with Video 2 info
    cout << "Initializing thread for Output Video..." << endl;
    thread write (outputVid, ref(readerMat1), ref(readerMat2), ref(reader1Flag), ref(reader2Flag), "Output Video", vidOutput, frameHeight, frameWidth);

    // get thread IDs
    thread::id id1 = read1.get_id();
    thread::id id2 = read2.get_id();
    thread::id id3 = write.get_id();


    // // synchronize threads:
    if (read1.joinable())
    {
        cout << "Joining thread for Video 1, ID = " << id1 << endl;
        read1.join();                // pauses until read1 finishes
    }
    
    if (read2.joinable())
    {
        cout << "Joining thread for Video 2, ID = " << id2 << endl;
        read2.join();               // pauses until read2 finishes
    }

    if (write.joinable())
    {
        cout << "Joining thread for Output Video, ID = " << id3 << endl;
        write.join();              // pauses until write finishes
    }

    cout << "Done outputting to file" << endl;
    destroyAllWindows();
    return 0;
}


int main(int, char**)
{
    
    
    string vid1Input = "./iris-tests/dynamic_test.mp4";
    string vid2Input = "./iris-tests/field_trees.avi";
    string vidOutput = "stitch.avi";
    
    int retVal;
    
    // Test 1
    //retVal = stitch (vid1Input, vid2Input, vidOutput); // wrap function to allow for testing
    
    // retVal = stitch("./initial-test/dynamic_test.mp4", "./initial-test/field_trees.avi", "./test-outputs/test1.avi" )
    // cout << "Test 1 Return: " << retVal << endl;    
    
    // retVal = stitch ("./custom-tests/empty.avi", "./custom-tests/regular.mp4", "./test-outputs/testmp4"); 
    // cout << "Test 2 Return: " << retVal << endl;    
    
    // retVal = stitch ("./custom-tests/pic.jpg","./custom-tests/regular.mp4", "./test-outputs/test3.avi"); 
    // cout << "Test 3 Return: " << retVal << endl;    
    
    // retVal = stitch ("./custom-tests/null.avi","./custom-tests/null.avi", "./test-outputs/test4.avi"); 
    // cout << "Test 4 Return: " << retVal << endl;    

    retVal = stitch ("./custom-tests/large.mp4","./custom-tests/regular.mp4", "./test-outputs/test5.avi"); 
    cout << "Test 5 Return: " << retVal << endl;   
    
    
    return retVal;

}