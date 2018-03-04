// #include "opencv2/opencv.hpp"
// #include <iostream>
// #include <stdio.h>
// #include <thread>
// #include <string>
// #include <queue>

// using namespace cv;
// using namespace std;


// struct myMat
// {
//     cv::Mat frame; /// Standard cv::Mat
//     string inputFile;
//     myMat(){};   /// Default constructor
//     ~myMat(){};  /// Destructor (called by queue::pop)
 
//     /// Copy constructor (called by queue::push)
//     myMat(const myMat& src)
//     {
//         src.frame.copyTo(frame);
//     }
// };


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

// void outputVid (VideoCapture& vid, string outputWindow, string outputFile)
// {
//     // Default resolution of the frame is obtained.The default resolution is system dependent. 
//     int frameWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
//     int frameHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 
//     double frameRate = vid.get(CV_CAP_PROP_FPS);
    
//     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     // VideoWriter vidOut(outputFile,CV_FOURCC('M','P','J','G'), 30, Size(frameWidth,frameHeight)); 
//     VideoWriter vidOut(outputFile, -1 , 30, Size(frameWidth,frameHeight)); 
//     while(1)
//     { 
//     Mat frame; 
        
//     // Capture frame-by-frame 
//     vid >> frame;

//     // If the frame is empty, break immediately
//     if (frame.empty())
//         break;
//     bitwise_not (frame, frame); // invert frame
//     // Write the frame into the file 'outcpp.avi'
//     vidOut.write(frame);

//     //cout << "Writing to file " << outputFile << endl;
//     // Display the resulting frame    
//     imshow( outputWindow, frame );

//     // Press  ESC on keyboard to  exit
//     char c = (char)waitKey(1);
//     if( c == 27 ) 
//         break;
//     }
// }

// void processVid(VideoCapture& vid, vector<Mat>& record, string vidInput)
// {
    
//     while(1)
//     {
//         Mat frame;
//         Mat enqueue;
//         vid >> frame; // get a new frame from video
//         if (frame.empty())
//             break;
//         bitwise_not (frame, frame);
//         cvtColor(frame, frame, CV_BGR2GRAY);
//         // imshow(outputWindow, frame);
//         // record.push(myMat()); // create a new empty mat
//         // frame.copyTo(record.front().frame);  // take a full copy
//         // record.front().inputFile = vidInput;
//         // enqueue.inputFile = vidInput;
//         // frame.copyTo(enqueue.frame);
//         frame.copyTo(enqueue);
//         record.push(enqueue);
        
//         cout << "Frame Size: " << (record.front()).size() << endl;
//         cout << vidInput << " Queue Size: " << record.size() << endl;
//         // cout << record.front().frame << endl;
//         // cout << record.front().inputFile << endl;
//         cout << "Reading from " << vidInput << endl;
//         if(waitKey(30) >= 0) break;
//     }
//     return;
// }



// void createVid( VideoCapture& vid, vector<Mat>& recordVid1, vector<Mat>& recordVid2, string outputFile)
// {
//     int frameWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
//     int frameHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 
//     double frameRate = vid.get(CV_CAP_PROP_FPS);
    
//     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     VideoWriter vidOut(outputFile, CV_FOURCC('M','P','J','G'), 10.0, Size(500,500)); 
//     Mat currFrame;
//     cout << "Starting to create video ..." << endl;
//     while (!recordVid1.empty() && !recordVid2.empty())
//     {
//         // if ((recordVid1.front().frame).empty() || (recordVid2.front().frame).empty())
//         //     break;
//         // //cout << "Writing to " << outputFile << endl;
//         // cout << recordVid1.front().inputFile << endl;
//         // cout << "Size of queue: " << recordVid1.size() << endl;
//         // cout << "Frame Size: " << (recordVid1.front().frame).size() << endl;
        
//         // vidOut.write(recordVid1.front().frame);
//         // recordVid1.pop();

//         // cout << recordVid2.front().inputFile << endl;
//         // cout << "Size of queue: " << recordVid2.size() << endl;
//         // cout << "Frame Size: " << (recordVid2.front().frame).size() << endl;
        
//         // vidOut.write(recordVid2.front().frame);
//         // recordVid2.pop();

//          if ((recordVid1.front()).empty() || (recordVid2.front()).empty())
//             break;
//         //cout << "Writing to " << outputFile << endl;
//         cout << "Size of queue: " << recordVid1.size() << endl;
//         cout << "Frame Size: " << (recordVid1.front()).size() << endl;
//         Mat frame;
//         (recordVid1.front()).copyTo(frame);
//         // vidOut.write(recordVid1.front());
//         vidOut.write(frame);
//         recordVid1.pop();

//         cout << "Size of queue: " << recordVid2.size() << endl;
//         cout << "Frame Size: " << (recordVid2.front()).size() << endl;
        
//         vidOut.write(recordVid2.front());
//         recordVid2.pop();
//         //imshow("Test", record.front());
        
//         if(waitKey(30) >= 0) break;
//     }

// }

// // void createVid( VideoCapture& vid, vector<Mat>& record, string outputFile)
// // {
// //     int frameWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
// //     int frameHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 
// //     double frameRate = vid.get(CV_CAP_PROP_FPS);
    
// //     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
// //     VideoWriter vidOut(outputFile,CV_FOURCC('M','P','J','G'), 10, Size(frameWidth,frameHeight)); 
// //     Mat currFrame;
// //     cout << "Starting to create video ..." << endl;
// //     while (!record.empty() && !recordVid2.empty())
// //     {
// //         if ((record.front().frame).empty() || (recordVid2.front().frame).empty())
// //             break;
// //         //cout << "Writing to " << outputFile << endl;
// //         cout << record.front().inputFile << endl;
// //         cout << "Size of queue: " << record.size() << endl;
// //         cout << "Frame Size: " << (record.front().frame).size() << endl;
        
// //         vidOut.write(record.front().frame);
// //         record.pop();

// //         cout << recordVid2.front().inputFile << endl;
// //         cout << "Size of queue: " << recordVid2.size() << endl;
// //         cout << "Frame Size: " << (recordVid2.front().frame).size() << endl;
        
// //         vidOut.write(recordVid2.front().frame);
// //         record.pop();
// //         //imshow("Test", record.front().frame);
        
// //         if(waitKey(10) >= 0) break;
// //     }

// // }

// void outputVid (VideoCapture& vid, vector<Mat>& record, string outputWindow, string outputFile)
// {
//     // Default resolution of the frame is obtained.The default resolution is system dependent. 
//     int frame_width = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
//     int frame_height = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 

//     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     // VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
//     VideoWriter vidOut(outputFile,CV_FOURCC('m', 'p', '4', 'v'),10, Size(frame_width,frame_height));
//     cout << vidOut.isOpened() << endl;
//     cout << frame_width << " X " << frame_height << endl;
//     cout << (record.front()).size() << endl;
//     while(1)
//     { 
//     Mat frame; 
          
//     // Capture frame-by-frame 
//     if (record.empty())
//         break;
//     // frame = record.front();
//     (record.front()).copyTo(frame);
    
//     // If the frame is empty, break immediately
//     if (frame.empty())
//         break;
//     //bitwise_not (frame, frame); // invert frame
//     // cout << frame << endl;
//     // Write the frame into the file 'outcpp.avi'
//     vidOut.write(frame);
//     // vidOut.operator << (frame);
//     // Display the resulting frame    
//     imshow( outputWindow, frame );
//     record.pop();
//     // Press  ESC on keyboard to  exit
//     char c = (char)waitKey(30);
//     if( c == 27 ) 
//         break;
//     }
// }

// int main(int, char**)
// {
//     // int frameHeight;
//     // int frameWidth;
//     // int frameRate;
    
//     string vid1Location = "./test5.mp4";
//     string vid2Location = "./test6.mp4";

//     string vid1Input = "test5.mp4";
//     string vid2Input = "test6.mp4";

//     string vid1Output = "work.avi";
//     string vid2Output = "video2.avi";

//     vector<Mat> vid1Queue;
//     vector<Mat> vid2Queue;
    
//     VideoCapture vid1(vid1Location); // open the first test file
//     if(!vid1.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 1 File could not be successfully opened" << endl;
//         return -1;
//     }

//     VideoCapture vid2(vid2Location); // open the second test file
//     if(!vid2.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 2 File could not be successfully opened" << endl;
//         return -1;
//     }

//     cout << "Initializing thread to process Video 1..." << endl;
//     // thread out1 (outputVid, ref(vid1), "Video 1 Output", vid1Output);     // spawn new thread that calls foo()
//     thread out1 (processVid, ref(vid1), ref(vid1Queue), vid1Input);     // spawn new thread that calls foo()
//     cout << "Initializing thread to process Video 2..." << endl;
//     thread out2 (processVid, ref(vid2), ref(vid2Queue), vid2Input);  // spawn new thread that calls bar(0)
    
//     // cout << "Initializing thread to create output video...";
//     // thread out3 (createVid, ref(vid2), ref(vid1Queue), ref(vid2Queue), vid1Output);
   
//     thread::id id1 = out1.get_id();
//     thread::id id2 = out2.get_id();
//     // thread::id id3 = out3.get_id();
//     // cout << "Streaming of two videos now executing concurrently...\n";

//     // // synchronize threads:
//     if (out1.joinable())
//     {
//         cout << "Joining thread for Video 1, ID = " << id1 << endl;
//         out1.join();                // pauses until first finishes
//     }
    
   
//     if (out2.joinable())
//     {
//         cout << "Joining thread for Video 2, ID = " << id2 << endl;
//         out2.join();               // pauses until second finishes
//     }

//     outputVid(vid2, vid2Queue, "Hi", "do.avi");
//     // if (out3.joinable())
//     // {
//     //     cout << "Joining thread for Output Video, ID = " << id3 << endl;
//     //     out3.join();               // pauses until second finishes
//     // }

//      // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     // VideoWriter vidOut(vid2Output, CV_FOURCC('M','P','J','G'), 10, Size(500,500)); 
//     // Mat currFrame;
//     // cout << "Starting to create video ..." << endl;
//     // while (!vid1Queue.empty() && !vid2Queue.empty())
//     // {
//     //     // if ((vid1Queue.front().frame).empty() || (vid2Queue.front().frame).empty())
//     //     //     break;
//     //     // //cout << "Writing to " << outputFile << endl;
//     //     // cout << vid1Queue.front().inputFile << endl;
//     //     // cout << "Size of queue: " << vid1Queue.size() << endl;
//     //     // cout << "Frame Size: " << (vid1Queue.front().frame).size() << endl;
        
//     //     // vidOut.write(vid1Queue.front().frame);
//     //     // vid1Queue.pop();

//     //     // cout << vid2Queue.front().inputFile << endl;
//     //     // cout << "Size of queue: " << vid2Queue.size() << endl;
//     //     // cout << "Frame Size: " << (vid2Queue.front().frame).size() << endl;
        
//     //     // vidOut.write(vid2Queue.front().frame);
//     //     // vid2Queue.pop();

//     //      if ((vid1Queue.front()).empty() || (vid2Queue.front()).empty())
//     //         break;
//     //     //cout << "Writing to " << outputFile << endl;
//     //     cout << "Size of queue: " << vid1Queue.size() << endl;
//     //     cout << "Frame Size: " << (vid1Queue.front()).size() << endl;
//     //     Mat frame;
//     //     (vid1Queue.front()).copyTo(frame);
//     //     // vidOut.write(vid1Queue.front());
//     //     vidOut.write(frame);
//     //     vid1Queue.pop();

//     //     cout << "Size of queue: " << vid2Queue.size() << endl;
//     //     cout << "Frame Size: " << (vid2Queue.front()).size() << endl;
        
//     //     vidOut.write(vid2Queue.front());
//     //     vid2Queue.pop();
//     //     //imshow("Test", record.front());
        
//     //     if(waitKey(30) >= 0) break;
//     // }

//     // cout << "Done outputting to file" << endl;

//     // cout << (vid2Queue.front().frame).size() << endl;
//     // vid2Queue.pop();
//     // cout << (vid2Queue.front().frame).size() << endl;
//     // vid2Queue.pop();
//     // cout << (vid2Queue.front().frame).size() << endl;
//     // cout << (vid2Queue.front().frame).size() << endl;
//     // vid2Queue.pop();
//     // cout << (vid2Queue.front().frame).size() << endl;

//     // createVid( ref(vid2), ref(vid1Queue), ref(vid2Queue), vid1Output);

//     // the camera will be deinitialized automatically in VideoCapture destructor
//     destroyAllWindows();
//     return 0;
// }

// #include "opencv2/opencv.hpp"
// #include <iostream>
// #include <stdio.h>
// #include <thread>
// #include <string>

// using namespace cv;
// using namespace std;

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

// void outputVid (VideoCapture& vid, string outputWindow, string outputFile)
// {
//     // Default resolution of the frame is obtained.The default resolution is system dependent. 
//     int frame_width = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
//     int frame_height = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 

//     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
//     while(1)
//     { 
//     Mat frame; 
        
//     // Capture frame-by-frame 
//     vid >> frame;

//     // If the frame is empty, break immediately
//     if (frame.empty())
//         break;
//     bitwise_not ( frame, frame); // invert frame
//     // Write the frame into the file 'outcpp.avi'
//     vidOut.write(frame);

//     // Display the resulting frame    
//     imshow( outputWindow, frame );

//     // Press  ESC on keyboard to  exit
//     char c = (char)waitKey(1);
//     if( c == 27 ) 
//         break;
//     }
// }

// int main(int, char**)
// {
//     string vid1Location = "./iris-tests/dynamic_test.mp4";
//     string vid2Location = "./iris-tests/field_trees.avi";

//     string vid1Output = "video1.avi";
//     string vid2Output = "video2.avi";
    
//     VideoCapture vid1(vid1Location); // open the first test file
//     if(!vid1.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 1 File could not be successfully opened" << endl;
//         return -1;
//     }

//     VideoCapture vid2(vid2Location); // open the second test file
//     if(!vid2.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 2 File could not be successfully opened" << endl;
//         return -1;
//     }

//     cout << "Initializing thread for Video 1..." << endl;
//     thread out1 (outputVid, ref(vid1), "Video 1 Output", vid1Output);     // spawn new thread that calls foo()
//     cout << "Initializing thread for Video 2..." << endl;
//     thread out2 (outputVid, ref(vid2), "Video 2 Output", vid2Output);  // spawn new thread that calls bar(0)

//     thread::id id1 = out1.get_id();
//     thread::id id2 = out2.get_id();
//     // cout << "Streaming of two videos now executing concurrently...\n";

//     // // synchronize threads:
//     if (out1.joinable())
//     {
//         cout << "Joining thread for Video 1, ID = " << id1 << endl;
//         out1.join();                // pauses until first finishes
//     }
    
//     if (out2.joinable())
//     {
//         cout << "Joining thread for Video 2, ID = " << id2 << endl;
//         out2.join();               // pauses until second finishes
//     }

//     // cout << "Streaming completed.\n";

//     //stream(vid1, "Video 1 Output");

    
//     // for(;;)
//     // {
//     //     Mat frame;
//     //     vid >> frame; // get a new frame from video
//     //     //invert(frame);
//     //     //cvtColor(frame, edges, CV_BGR2GRAY);
//     //     // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
//     //     // Canny(edges, edges, 0, 30, 3);
//     //     bitwise_not ( frame, frame);
//     //     imshow("Output Video", frame);
//     //     if(waitKey(30) >= 0) break;
//     // }
//     // the camera will be deinitialized automatically in VideoCapture destructor
//     destroyAllWindows();
//     return 0;
// }

// #include "opencv2/opencv.hpp"
// #include <iostream>
// #include <stdio.h>
// #include <thread>
// #include <string>
// #include <queue>
// #include <vector>

// using namespace cv;
// using namespace std;


// void processVid(VideoCapture& vid, vector<Mat>& record, string vidInput)
// {
    
//     while(1)
//     {
//         Mat frame;
//         Mat enqueue;
//         vid >> frame; // get a new frame from video
//         if (frame.empty())
//             break;
//         bitwise_not (frame, frame);
//         cvtColor(frame, frame, CV_BGR2GRAY);
//         // imshow(outputWindow, frame);
//         // record.push(myMat()); // create a new empty mat
//         // frame.copyTo(record.front().frame);  // take a full copy
//         // record.front().inputFile = vidInput;
//         // enqueue.inputFile = vidInput;
//         // frame.copyTo(enqueue.frame);
//         frame.copyTo(enqueue);
//         record.push_back(enqueue);
        
//         cout << "Frame Size: " << (record.front()).size() << endl;
//         cout << vidInput << " Queue Size: " << record.size() << endl;
//         // cout << record.front().frame << endl;
//         // cout << record.front().inputFile << endl;
//         cout << "Reading from " << vidInput << endl;
//         if(waitKey(30) >= 0) break;
//     }
//     return;
// }

// void outputVid (VideoCapture& vid, vector<Mat>& record, string outputWindow, string outputFile)
// {
//     // Default resolution of the frame is obtained.The default resolution is system dependent. 
//     int frame_width = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
//     int frame_height = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 

//     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     // VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
//     VideoWriter vidOut(outputFile,CV_FOURCC('m', 'p', '4', 'v'),10, Size(frame_width,frame_height));
//     cout << vidOut.isOpened() << endl;
//     cout << frame_width << " X " << frame_height << endl;
//     // cout << ((record[0]).size() << endl;
//     int i = 0;
//     while(1)
//     { 
//     Mat frame = record[i];
          
//     // Capture frame-by-frame 
//     // if (record.empty())
//     //     break;
//     if (i >= record.size())
//         break;
//     // frame = record.front();
//    // (record[0]).copyTo(frame);
    
//     // If the frame is empty, break immediately
//     if (frame.empty())
//         break;
//     //bitwise_not (frame, frame); // invert frame
//     // cout << frame << endl;
//     // Write the frame into the file 'outcpp.avi'
//     // cout << (record[0]) << endl;
//     vidOut.write(record[i]);
//     // vidOut.operator << (frame);
//     // Display the resulting frame    
//     imshow( outputWindow, frame );
//     record.erase(record.begin());
//     // Press  ESC on keyboard to  exit
//     char c = (char)waitKey(30);
//     if( c == 27 ) 
//         break;
//     }
//     i++;
// }

// int main(int, char**)
// {
//     // int frameHeight;
//     // int frameWidth;
//     // int frameRate;
    
//     string vid1Location = "./test5.mp4";
//     string vid2Location = "./test6.mp4";

//     string vid1Input = "test5.mp4";
//     string vid2Input = "test6.mp4";

//     string vid1Output = "work.avi";
//     string vid2Output = "video2.avi";

//     vector<Mat> vid1Queue;
//     vector<Mat> vid2Queue;
    
//     VideoCapture vid1(vid1Location); // open the first test file
//     if(!vid1.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 1 File could not be successfully opened" << endl;
//         return -1;
//     }

//     VideoCapture vid2(vid2Location); // open the second test file
//     if(!vid2.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 2 File could not be successfully opened" << endl;
//         return -1;
//     }

//     cout << "Initializing thread to process Video 1..." << endl;
//     // thread out1 (outputVid, ref(vid1), "Video 1 Output", vid1Output);     // spawn new thread that calls foo()
//     thread out1 (processVid, ref(vid1), ref(vid1Queue), vid1Input);     // spawn new thread that calls foo()
//     cout << "Initializing thread to process Video 2..." << endl;
//     thread out2 (processVid, ref(vid2), ref(vid2Queue), vid2Input);  // spawn new thread that calls bar(0)
    
//     // cout << "Initializing thread to create output video...";
//     // thread out3 (createVid, ref(vid2), ref(vid1Queue), ref(vid2Queue), vid1Output);
   
//     thread::id id1 = out1.get_id();
//     thread::id id2 = out2.get_id();
//     // thread::id id3 = out3.get_id();
//     // cout << "Streaming of two videos now executing concurrently...\n";

//     // // synchronize threads:
//     if (out1.joinable())
//     {
//         cout << "Joining thread for Video 1, ID = " << id1 << endl;
//         out1.join();                // pauses until first finishes
//     }
    
   
//     if (out2.joinable())
//     {
//         cout << "Joining thread for Video 2, ID = " << id2 << endl;
//         out2.join();               // pauses until second finishes
//     }

//     outputVid(vid2, vid2Queue, "Hi", "do.avi");
//     // if (out3.joinable())
//     // {
//     //     cout << "Joining thread for Output Video, ID = " << id3 << endl;
//     //     out3.join();               // pauses until second finishes
//     // }

//      // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     // VideoWriter vidOut(vid2Output, CV_FOURCC('M','P','J','G'), 10, Size(500,500)); 
//     // Mat currFrame;
//     // cout << "Starting to create video ..." << endl;
//     // while (!vid1Queue.empty() && !vid2Queue.empty())
//     // {
//     //     // if ((vid1Queue.front().frame).empty() || (vid2Queue.front().frame).empty())
//     //     //     break;
//     //     // //cout << "Writing to " << outputFile << endl;
//     //     // cout << vid1Queue.front().inputFile << endl;
//     //     // cout << "Size of queue: " << vid1Queue.size() << endl;
//     //     // cout << "Frame Size: " << (vid1Queue.front().frame).size() << endl;
        
//     //     // vidOut.write(vid1Queue.front().frame);
//     //     // vid1Queue.pop();

//     //     // cout << vid2Queue.front().inputFile << endl;
//     //     // cout << "Size of queue: " << vid2Queue.size() << endl;
//     //     // cout << "Frame Size: " << (vid2Queue.front().frame).size() << endl;
        
//     //     // vidOut.write(vid2Queue.front().frame);
//     //     // vid2Queue.pop();

//     //      if ((vid1Queue.front()).empty() || (vid2Queue.front()).empty())
//     //         break;
//     //     //cout << "Writing to " << outputFile << endl;
//     //     cout << "Size of queue: " << vid1Queue.size() << endl;
//     //     cout << "Frame Size: " << (vid1Queue.front()).size() << endl;
//     //     Mat frame;
//     //     (vid1Queue.front()).copyTo(frame);
//     //     // vidOut.write(vid1Queue.front());
//     //     vidOut.write(frame);
//     //     vid1Queue.pop();

//     //     cout << "Size of queue: " << vid2Queue.size() << endl;
//     //     cout << "Frame Size: " << (vid2Queue.front()).size() << endl;
        
//     //     vidOut.write(vid2Queue.front());
//     //     vid2Queue.pop();
//     //     //imshow("Test", record.front());
        
//     //     if(waitKey(30) >= 0) break;
//     // }

//     // cout << "Done outputting to file" << endl;

//     // cout << (vid2Queue.front().frame).size() << endl;
//     // vid2Queue.pop();
//     // cout << (vid2Queue.front().frame).size() << endl;
//     // vid2Queue.pop();
//     // cout << (vid2Queue.front().frame).size() << endl;
//     // cout << (vid2Queue.front().frame).size() << endl;
//     // vid2Queue.pop();
//     // cout << (vid2Queue.front().frame).size() << endl;

//     // createVid( ref(vid2), ref(vid1Queue), ref(vid2Queue), vid1Output);

//     // the camera will be deinitialized automatically in VideoCapture destructor
//     destroyAllWindows();
//     return 0;
// }

// // #include "opencv2/opencv.hpp"
// // #include <iostream>
// // #include <stdio.h>
// // #include <thread>
// // #include <string>
// // #include <queue>

// // using namespace cv;
// // using namespace std;

// // void processVid(VideoCapture& vid, queue<Mat>& record, string vidInput)
// // {
    
// //     while(1)
// //     {
// //         Mat frame;
// //         Mat enqueue;
// //         vid >> frame; // get a new frame from video
// //         if (frame.empty())
// //             break;
// //         bitwise_not (frame, frame);
// //         cvtColor(frame, frame, CV_BGR2GRAY);
// //         // imshow(outputWindow, frame);
// //         // record.push(myMat()); // create a new empty mat
// //         // frame.copyTo(record.front().frame);  // take a full copy
// //         // record.front().inputFile = vidInput;
// //         // enqueue.inputFile = vidInput;
// //         // frame.copyTo(enqueue.frame);
// //         frame.copyTo(enqueue);
// //         record.push(enqueue);
        
// //         cout << "Frame Size: " << (record.front()).size() << endl;
// //         cout << vidInput << " Queue Size: " << record.size() << endl;
// //         // cout << record.front().frame << endl;
// //         // cout << record.front().inputFile << endl;
// //         cout << "Reading from " << vidInput << endl;
// //         if(waitKey(30) >= 0) break;
// //     }
// //     return;
// // }



// void outputVid (VideoCapture& vid, queue<Mat>& record, string outputWindow, string outputFile)
// {
//     // Default resolution of the frame is obtained.The default resolution is system dependent. 
//     int frame_width = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
//     int frame_height = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 

//     // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
//     VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
//     // VideoWriter vidOut(outputFile,CV_FOURCC('D', 'I', 'V', 'X'),25, Size(frame_width,frame_height));
//     cout << vidOut.isOpened() << endl;
//     cout << frame_width << " X " << frame_height << endl;
//     cout << (record.front()).size() << endl;
//     while(1)
//     { 
//     Mat frame; 
          
//     // Capture frame-by-frame 
//     if (record.empty())
//         break;
//     // frame = record.front();
//     (record.front()).copyTo(frame);
    
//     // If the frame is empty, break immediately
//     if (frame.empty())
//         break;
//     //bitwise_not (frame, frame); // invert frame
//     // cout << frame << endl;
//     // Write the frame into the file 'outcpp.avi'
//     resize(frame,frame,Size(frame_width, frame_height));
//     vidOut.write(frame);
//     //  vidOut.write(record.front());
//     // vidOut.operator << (frame);
//     // Display the resulting frame    
//     imshow( outputWindow, frame );
//     record.pop();
//     // Press  ESC on keyboard to  exit
//     char c = (char)waitKey(30);
//     if( c == 27 ) 
//         break;
//     }
// }

// int main(int, char**)
// {
//     // int frameHeight;
//     // int frameWidth;
//     // int frameRate;
    
//     string vid1Location = "./test5.mp4";
//     string vid2Location = "./test6.mp4";

//     string vid1Input = "test5.mp4";
//     string vid2Input = "test6.mp4";

//     string vid1Output = "work.avi";
//     string vid2Output = "video2.avi";

//     queue<Mat> vid1Queue;
//     queue<Mat> vid2Queue;
    
//     VideoCapture vid1(vid1Location); // open the first test file
//     if(!vid1.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 1 File could not be successfully opened" << endl;
//         return -1;
//     }

//     VideoCapture vid2(vid2Location); // open the second test file
//     if(!vid2.isOpened())  // check if we succeeded
//     { 
//         cout << "Video 2 File could not be successfully opened" << endl;
//         return -1;
//     }

//     cout << "Initializing thread to process Video 1..." << endl;
//     // thread out1 (outputVid, ref(vid1), "Video 1 Output", vid1Output);     // spawn new thread that calls foo()
//     thread out1 (processVid, ref(vid1), ref(vid1Queue), vid1Input);     // spawn new thread that calls foo()
//     cout << "Initializing thread to process Video 2..." << endl;
//     thread out2 (processVid, ref(vid2), ref(vid2Queue), vid2Input);  // spawn new thread that calls bar(0)
    
//     // cout << "Initializing thread to create output video...";
//     // thread out3 (createVid, ref(vid2), ref(vid1Queue), ref(vid2Queue), vid1Output);
   
//     thread::id id1 = out1.get_id();
//     thread::id id2 = out2.get_id();
//     // thread::id id3 = out3.get_id();
//     // cout << "Streaming of two videos now executing concurrently...\n";

//     // // synchronize threads:
//     if (out1.joinable())
//     {
//         cout << "Joining thread for Video 1, ID = " << id1 << endl;
//         out1.join();                // pauses until first finishes
//     }
    
   
//     if (out2.joinable())
//     {
//         cout << "Joining thread for Video 2, ID = " << id2 << endl;
//         out2.join();               // pauses until second finishes
//     }

//     outputVid(vid2, vid2Queue, "Hi", "doit.avi");
//     // if (out3.joinable())
//     // {
//     //     cout << "Joining thread for Output Video, ID = " << id3 << endl;
//     //     out3.join();               // pauses until second finishes
//     // }

//     destroyAllWindows();
//     return 0;
// }

#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <string>

using namespace cv;
using namespace std;

#define OUTPUT_FPS 30

bool readersDone = false;

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

void outputVid ( Mat& readerMat1, Mat& readerMat2, bool& reader1, bool& reader2, string outputWindow, string outputFile, int frameHeight, int frameWidth)
{
    // // Default resolution of the frame is obtained.The default resolution is system dependent. 
    // int frame_width = vid.get(CV_CAP_PROP_FRAME_WIDTH); 
    // int frame_height = vid.get(CV_CAP_PROP_FRAME_HEIGHT); 

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
    cout << "Starting to write to file..." << endl;
    VideoWriter vidOut(outputFile,CV_FOURCC('M','J','P','G'),OUTPUT_FPS, Size(frameWidth,frameHeight)); 
    while(1)
    { 
    
    // if (reader1Done == true)
    // {
    //     break;
    // }
    // if (reader2Done ==  true)
    // cout << "Start checking for conditions writer" << endl;

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
        Mat frame;

        // resize(readerMat1,readerMat1,Size(frameWidth, frameHeight));
        resize(readerMat1,frame,Size(frameWidth, frameHeight));
        //cout << readerMat1.size() << endl;
        //if (readerMat1.size() == Size(frameWidth, frameHeight))
        // vidOut.write(readerMat1);
        vidOut.write(frame);
        // imshow( outputWindow, readerMat1 );
    }


    while (reader2 == false && readersDone == false)
    {
        // cout << "Waiting for next Reader 2 frame..." << endl;
    }  // waits
    //readerMat2.copyTo(frame);
    if (reader2 == true && readersDone == false)
    {
        reader2 = false;
        if (readerMat2.empty())
            break;
        resize(readerMat2,readerMat2,Size(frameWidth, frameHeight));
        vidOut.write(readerMat2);
        // imshow( outputWindow, readerMat2 ); // Display the resulting frame 
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


int main(int, char**)
{
    // string vid1Input = "test5.mp4";
    // string vid2Input = "tesst6.mp4";

    string vid1Input = "./iris-tests/dynamic_test.mp4";
    string vid2Input = "./iris-tests/field_trees.avi";

    string vid1Output = "video1.avi";
    string vid2Output = "video2.avi";


    int frameHeight;
    int frameWidth;

    Mat readerMat1;
    Mat readerMat2;

    bool reader1Flag = false;
    bool reader2Flag = false;
    
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
    }
    else
    {
        frameWidth = vid2.get(CV_CAP_PROP_FRAME_WIDTH);
    }

    cout << frameHeight << endl;
    cout << frameWidth << endl;
    
    cout << "Initializing thread for Video 1..." << endl;
    thread out1 (reader, ref(vid1), ref(readerMat1), ref(reader1Flag), vid1Input);     // spawn new thread that calls foo()
    cout << "Initializing thread for Video 2..." << endl;
    thread out2 (reader, ref(vid2), ref(readerMat2), ref(reader2Flag), vid2Input);  // spawn new thread that calls bar(0)
    cout << "Initializing thread for Output Video..." << endl;
    thread out3 (outputVid, ref(readerMat1), ref(readerMat2), ref(reader1Flag), ref(reader2Flag), "Output Video", vid2Output, frameHeight, frameWidth);

    thread::id id1 = out1.get_id();
    thread::id id2 = out2.get_id();
    thread::id id3 = out3.get_id();
    // // cout << "Streaming of two videos now executing concurrently...\n";

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

    if (out3.joinable())
    {
        cout << "Joining thread for Output Video, ID = " << id3 << endl;
        out3.join();
    }

    cout << "Done outputting to file" << endl;
    destroyAllWindows();
    return 0;
}
