#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <string>

using namespace cv;
using namespace std;

#define OUTPUT_FPS 30

bool readersDone = false;

// void stream (VideoCapture& vid, string outputWindow)
// {
//     namedWindow(outputWindow, WINDOW_NORMAL);
//     while(1)
//     {
//         Mat frame;
//         vid >> frame; // get a new frame from video
//         if (frame.empty())
//             break;
//         bitwise_not ( frame, frame);
//         imshow(outputWindow, frame);
//         if(waitKey(30) >= 0) break;
//     }
//     return;
// }

void outputVid ( Mat& readerMat1, Mat& readerMat2, bool& reader1, bool& reader2, string outputWindow, string outputFile, int frameHeight, int frameWidth)
{
    cout << "Starting to write to file..." << endl;
    VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),OUTPUT_FPS, Size(frameWidth,frameHeight)); 
    while(1)
    { 

    if (readersDone == true)
        break;
    
   
    while (reader1 == false && readersDone == false)
    {
        // cout << "Waiting for next Reader 1 frame..." << endl;
    } //wait
    // readerMat1.copyTo(frame);    
    if (reader1 == true && readersDone == false)
    {
        reader1 = false;
        if (readerMat1.empty())
            break;

        resize(readerMat1,readerMat1,Size(frameWidth, frameHeight));
        vidOut.write(readerMat1);

    }


    while (reader2 == false && readersDone == false)
    {
        // cout << "Waiting for next Reader 2 frame..." << endl;
    }  // waits
  
    if (reader2 == true && readersDone == false)
    {
        reader2 = false;
        if (readerMat2.empty())
            break;
    
        resize(readerMat2,readerMat2,Size(frameWidth, frameHeight));
        vidOut.write(readerMat2);
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
    // cvtColor(readerMat, readerMat, CV_BGR2GRAY);
    bitwise_not ( readerMat, readerMat); // invert readerMat
    
    if (readerMat.empty())
        break; // stop reading because the current video is over
    // frame.copyTo(readerMat);
    reader = true; // indicate that this reader's value is ready to be writter
    char c = (char)waitKey(1);
    if( c == 27 ) 
        break;
    
    }
    cout << "Reader is done capturing frames from " << vidInput << endl;
    readersDone = true; // set readersDone flag to true because reader has finished 
    return;
}



class Reader 
{
    private:
        
        //thread readThread(&Reader::read, this);
        //thread::id id = thread.get_id();
        // thread processThread;
        // thread::id id;
        
    public:
        bool reader;
        Mat readerMat;
        VideoCapture vid;
        string vidInput;
        //static bool readersDone;
        Reader()
        {};
        Reader (VideoCapture& vid, string vidInput)
        {
            //readersDone = false;
            //reader = false;
            this->vid = vid;
            this->vidInput = vidInput;
        };
        ~Reader(){};
        // {
        //     processThread.join();
        // };
        // void read(void);
        // void runThreaded(void)
        // {
        //     processThread = thread(&Reader::read, this);
        //     id = processThread.get_id();
        // };
    protected: 
        
        
};

// void Reader::read (void)
// {
//     cout << vidInput << " Reader Active" << endl;
//     while(1)
//     { 

//     if (readersDone == true)
//     {
//         reader = false;
//         break; // stop reading because one of the videos is over
//     }
   
//     while (reader != false && readersDone == false)
//     {
//        // wait until writer needs a new value
//     }
//     vid >> readerMat;
//     // cvtColor(readerMat, readerMat, CV_BGR2GRAY);
//     bitwise_not ( readerMat, readerMat); // invert readerMat
    
//     if (readerMat.empty())
//         break; // stop reading because the current video is over
//     // frame.copyTo(readerMat);
//     reader = true; // indicate that this reader's value is ready to be written
//     char c = (char)waitKey(1);
//     if( c == 27 ) 
//         break;
    
//     }
//     cout << "Reader is done capturing frames from " << vidInput << endl;
//     readersDone = true; // set readersDone flag to true because reader has finished 
//     return;
// }

class Writer
{
    private:

        Reader vid1;
        Reader vid2;
    
    public: 
        //static bool readersDone;
        int frameHeight;
        int frameWidth;
        string outputFile;
        Writer(){};
        Writer (Reader& inVid1, Reader& inVid2, string outputFile )
        {
            this->vid1 = inVid1;
            this->vid1 = inVid1;
            this->outputFile = outputFile;

            //readersDone = false;
            
            // choose frame height and frame width corresponding to the smallest dimensions present in both videos
    
            // choose smallest frame height
            if (vid1.vid.get(CV_CAP_PROP_FRAME_HEIGHT) <= vid2.vid.get(CV_CAP_PROP_FRAME_HEIGHT))
            {
                frameHeight = vid1.vid.get(CV_CAP_PROP_FRAME_HEIGHT);
            }
            else
            {
                frameHeight = vid2.vid.get(CV_CAP_PROP_FRAME_HEIGHT);
            }

            // choose smallest frame width
            if (vid1.vid.get(CV_CAP_PROP_FRAME_WIDTH) <= vid2.vid.get(CV_CAP_PROP_FRAME_WIDTH))
            {
                frameWidth = vid1.vid.get(CV_CAP_PROP_FRAME_WIDTH);
            }
            else
            {
                frameWidth = vid2.vid.get(CV_CAP_PROP_FRAME_WIDTH);
            }

        }
        ~Writer(){};
        // {
        //     processThread.join();
        // };
        // void write(void);
        // void runThreaded(void)
        // {
        //     processThread = thread(&Writer::write, this);
        //     id = processThread.get_id();
        // }
    protected:
        
};

// void Writer::write (void)
// {
//     cout << "Starting to write to file..." << endl;
//     VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),OUTPUT_FPS, Size(frameWidth,frameHeight)); 
//     while(1)
//     { 

//     if (readersDone == true)
//         break;
    
   
//     while (vid1.reader == false && readersDone == false)
//     {
//         // cout << "Waiting for next Reader 1 frame..." << endl;
//     } //wait
//     // readerMat1.copyTo(frame);    
//     if (vid1.reader == true && readersDone == false)
//     {
//         vid1.reader = false;
//         if (vid1.readerMat.empty())
//             break;

//         resize(vid1.readerMat,vid1.readerMat,Size(frameWidth, frameHeight));
//         vidOut.write(vid1.readerMat);

//     }


//     while (vid2.reader == false && readersDone == false)
//     {
//         // cout << "Waiting for next Reader 2 frame..." << endl;
//     }  // waits
  
//     if (vid2.reader == true && readersDone == false)
//     {
//         vid2.reader = false;
//         if (vid2.readerMat.empty())
//             break;
    
//         resize(vid2.readerMat,vid2.readerMat,Size(frameWidth, frameHeight));
//         vidOut.write(vid2.readerMat);
//     }
        

//     // Press  ESC on keyboard to  exit
//     char c = (char)waitKey(1);
//     if( c == 27 ) 
//         break;
//     }

//     cout << "Finished writing to output file." << endl;
// }

int main(int, char**)
{
    // string vid1Input = "test5.mp4";
    // string vid2Input = "tesst6.mp4";

    string vid1Input = "./iris-tests/dynamic_test.mp4";
    string vid2Input = "./iris-tests/field_trees.avi";

    string outputFile = "stitch.avi";
    


    // int frameHeight;
    // int frameWidth;

    // Mat readerMat1;
    // Mat readerMat2;

    // bool reader1Flag = false;
    // bool reader2Flag = false;
    
    VideoCapture vid1(vid1Input); // open the first test file
    if(!vid1.isOpened())  // check if we succeeded
    { 
        cout << "Video 1 File could not be successfully opened" << endl;
        return -1;
    }

    VideoCapture vid2(vid2Input); // open the second test file
    if(!vid2.isOpened())  // check if we succeeded
    { 
        cout << "Video 2 File could not be successfully opened" << endl;
        return -1;
    }

    cout << vid1.get(CV_CAP_PROP_FPS) << endl;
    cout << vid2.get(CV_CAP_PROP_FPS) << endl;

    // // choose frame height and frame width corresponding to the smallest dimensions present in both videos
    
    // // choose smallest frame height
    // if (vid1.get(CV_CAP_PROP_FRAME_HEIGHT) <= vid2.get(CV_CAP_PROP_FRAME_HEIGHT))
    // {
    //     frameHeight = vid1.get(CV_CAP_PROP_FRAME_HEIGHT);
    //     // vid2.set(CV_CAP_PROP_FRAME_HEIGHT, frameHeight);
    // }
    // else
    // {
    //     frameHeight = vid2.get(CV_CAP_PROP_FRAME_HEIGHT);
    //     // vid1.set(CV_CAP_PROP_FRAME_HEIGHT, frameHeight);
    // }

    // // choose smallest frame width
    // if (vid1.get(CV_CAP_PROP_FRAME_WIDTH) <= vid2.get(CV_CAP_PROP_FRAME_WIDTH))
    // {
    //     frameWidth = vid1.get(CV_CAP_PROP_FRAME_WIDTH);
    //     // vid2.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
    // }
    // else
    // {
    //     frameWidth = vid2.get(CV_CAP_PROP_FRAME_WIDTH);
    //     // vid1.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
    // }

    
    // cout << "Output Frame Width: " << frameWidth << endl;
    // cout << "Output Frame Height: " << frameHeight << endl;
    
    
    // cout << "Initializing thread for Video 1..." << endl;
    // thread out1 (reader, ref(vid1), ref(readerMat1), ref(reader1Flag), vid1Input);     // spawn new thread that calls foo()
    // cout << "Initializing thread for Video 2..." << endl;
    // thread out2 (reader, ref(vid2), ref(readerMat2), ref(reader2Flag), vid2Input);  // spawn new thread that calls bar(0)
    // cout << "Initializing thread for Output Video..." << endl;
    // thread out3 (outputVid, ref(readerMat1), ref(readerMat2), ref(reader1Flag), ref(reader2Flag), "Output Video", vid2Output, frameHeight, frameWidth);

    Reader reader1(ref(vid1), vid1Input);
    Reader reader2(ref(vid2), vid2Input);
    Writer writer(ref(reader1), ref(reader2), outputFile);

    cout << "Output Frame Width: " << writer.frameWidth << endl;
    cout << "Output Frame Height: " << writer.frameHeight << endl;
    
    
    cout << "Initializing thread for Video 1..." << endl;
    thread read1 (reader, ref(reader1.vid), ref(reader1.readerMat), ref(reader1.reader), reader1.vidInput);     // spawn new thread that calls foo()
    cout << "Initializing thread for Video 2..." << endl;
    thread read2 (reader, ref(reader2.vid), ref(reader2.readerMat), ref(reader2.reader), reader2.vidInput);  // spawn new thread that calls bar(0)
    cout << "Initializing thread for Output Video..." << endl;
    thread write (outputVid, ref(reader1.readerMat), ref(reader2.readerMat), ref(reader1.reader), ref(reader2.reader), "Output Video", writer.outputFile, writer.frameHeight, writer.frameWidth);


    // cout << "Initializing thread for Video 1..." << endl;
    // thread read1 (reader1.read);     // spawn new thread that calls foo()
    // cout << "Initializing thread for Video 2..." << endl;
    // thread read2 (reader2.read);  // spawn new thread that calls bar(0)
    // cout << "Initializing thread for Output Video..." << endl;
    // thread write (writer.write);

    thread::id id1 = read1.get_id();
    thread::id id2 = read2.get_id();
    thread::id id3 = write.get_id();
    // // cout << "Streaming of two videos now executing concurrently...\n";


    // // synchronize threads:
    if (read1.joinable())
    {
        cout << "Joining thread for Video 1, ID = " << id1 << endl;
        read1.join();                // pauses until first finishes
    }
    
    if (read2.joinable())
    {
        cout << "Joining thread for Video 2, ID = " << id2 << endl;
        read2.join();               // pauses until second finishes
    }

    if (write.joinable())
    {
        cout << "Joining thread for Output Video, ID = " << id3 << endl;
        write.join();
    }

    cout << "Done outputting to file" << endl;
    destroyAllWindows();
    return 0;
}
