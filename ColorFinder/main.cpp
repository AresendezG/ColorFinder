#include "ColorFinder_Header.h"
#include "OperationModes.h"
#include "CustomTypes.h"


#define CFVERSION "2.0.0.1" //Create a version of Colorfinder

using namespace cv;
using namespace std;

/*
    Author: Esli Alejandro Resendez
    ARGE Software, a brand of Rio Bravo Technologies, LLC
    
    License: 
        Open Source, feel free to copy or reuse this code as you desire. 
        Parts of this code were copied from various OpenCV's ORG own resource pages:
        https://answers.opencv.org/questions/
        https://docs.opencv.org/master/examples.html
        
    Disclaimer:    
    This software has no warranty of any kind. 

    Last update: 29 Noviembre 2022

    Last change summary:
    * Update the config to work with OpenCV 4.6
*/


//Global Variables
Mat img, placeholder;

/*
    For Snapshot mode:
    snapwdelay [Webcam Number 0...9] [c:/path/to/image.png] [delay(seconds)]

    argv[1] -> User Operation command (snapshot, filter, etc)
    argv[2] -> Camera Index
    argv[3] -> Image Save Path
    argv[4] -> Delay in seconds

    for other modes:
    argv[1] -> User operation command
    argv[2] -> Image Location
    arvg[3...n] -> Extra params


*/


//Main Function
int main(int argc, const char** argv)
{

    cv::String filename;
    std::string user_operation;
    cv::Mat img;
    ClickHandler click_data;

    click_data.isDragging = false;
    click_data.isReleased = true;
    click_data.rectangleSelected = false;
    int ErrCode = -1;
        
   try {

        cout << "Color Finder - Version "<< CFVERSION << endl;
        if (argv[0] == NULL || argv[1] == NULL){
            user_operation == "none";
        }
        else {
            user_operation = argv[1];
        }

        /* Will check if more than 2 args were passed*/
        if (argc > 2) {

            filename = String(argv[2]);
            OperationModes  mode;
            ErrCode = mode.loadImage(filename, img);

             if (ErrCode > 0) {

                /* Operation Image can be loaded so pick the Sw Operation*/
                if (user_operation == "show") {
                   //add timestamp example
                    mode.addTimeStamp(img);
                    imshow("Image Display", img);
                    cv::waitKey(0);
                }

                else if (user_operation == "FixedColorFilter") //Not Usable
                {
                    cv::Mat mask, filterImg;
                    double ColorFilterValues[3] = { 118,176,204 };
                    imshow("Image Display", img);
                    // mode.ColorFilter(img, ColorFilterValues[0], 40, mask);
                    imshow("Result Screen", mask);
                    cv::waitKey(0);
                }

                else if (user_operation == "pickColor_hover")
                {

                    mode.filename_str = filename;
                    ClickHandler click;
                    mode.PickColor(0, click);
                    while (1)
                    {
                        //setMouseCallback("Press ESC to Exit", onMouse);
                        char k = cv::waitKey(1) & 0xFF;
                        if (k == 27)
                            break;
                        //Check next image in the folder
                    }

                }

                else if (user_operation == "pickColor_click") {

                    ClickHandler click;
                    mode.filename_str = filename;
                    mode.PickColor(1, click);
                    while (1)
                    {
                        //setMouseCallback("Press ESC to Exit", onMouse);
                        char k = cv::waitKey(1) & 0xFF;
                        if (k == 27)
                            break;
                        //Check next image in the folder
                    }

                }

                else if (user_operation == "findROI_click") {

                    FilterValues FilterData;
                    mode.filename_str = filename;
                    mode.PickColor(2, click_data); // Set mouse callback and save everything on click data
                    while (1)
                    {
                        //setMouseCallback("Press ESC to Exit", onMouse);
                        char k = cv::waitKey(1) & 0xFF;
                        if (k == 27)
                            break;
                        if (click_data.rectangleSelected)
                        {
                            mode.Find_ROI(img, click_data.rectArea, FilterData);
                            click_data.rectangleSelected = false; //After drawing the ROI, wait for next
                        }
                        //Check next image in the folder
                    }

                }

                else if (user_operation == "colorFilter_mouse") {

                    Mat filtered_img;
                    Mat mask;
                    mode.filename_str = filename;
                    mode.PickColor(2, click_data); // Set mouse callback and save everything on click data
                    FilterValues FilterData;
                    while (1)
                    {
                        char k = cv::waitKey(1) & 0xFF;
                        if (k == 27)
                            break;

                        if (click_data.rectangleSelected)
                        {
                            mode.Find_ROI(img, click_data.rectArea, FilterData);
                            click_data.rectangleSelected = false; //After drawing the ROI, wait for next
                            mode.ColorFilter(img, FilterData, filtered_img, mask);
                            imshow("Filtered Colors", filtered_img);
                            cv::waitKey(0);
                            break;
                        }
                        //Check next image in the folder
                    }

                }

                else if (user_operation == "find_ROI") {

                    FilterValues FilterData;
                    cv::Rect roi;
                    roi.x = 200;
                    roi.y = 150;
                    roi.width = 300;
                    roi.height = 200;

                    if (ErrCode > 0) {

                        mode.Find_ROI(img, roi, FilterData);
                    }
                    else
                        std::cout << "Image cannot be loaded, Error Code" << endl;
                }

                else if (user_operation == "imageHasColor" || user_operation == "imageHasColorHSV") {

                    // User must pass Color filter as BBB,GGG,RRR max of 255 for each channel
                    std::string user_colorfilter, option2;
                    FilterValues FilterData;
                    Mat output, mask;

                    double TotalPixels; double NonZeroPixels;

                    if (argc > 4) {
                        user_colorfilter = argv[3];
                        option2 = argv[4];

                        int j = 0; int previousFound = 0;


                        /* Has color BGR and Tolerance level for each channel */

                        int filterValues_Array[6] = { 0,0,0,0,0,0 };

                        //StringContainer filter_str_array;

                        for (std::string::size_type i = 0; i < user_colorfilter.size(); ++i) {

                            if (user_colorfilter[i] == 44) //Comma delimiter
                            {
                                filterValues_Array[j] = stoi(user_colorfilter.substr(previousFound, i));
                                if (filterValues_Array[j] > 255)
                                    filterValues_Array[j] = 255;
                                if (filterValues_Array[j] < 0)
                                    filterValues_Array[j] = 0;

                                previousFound = i + 1;
                                j++;
                            }
                            if (j == 5) {
                                filterValues_Array[j] = stoi(user_colorfilter.substr(previousFound, i));
                                break;
                            }

                        }

                        FilterData.B = filterValues_Array[0];
                        FilterData.B_tolerance = filterValues_Array[3];
                        FilterData.G = filterValues_Array[1];
                        FilterData.G_tolerance = filterValues_Array[4];
                        FilterData.R = filterValues_Array[2];
                        FilterData.R_tolerance = filterValues_Array[5];

                        // imshow("Original Image", img);
                        if ("imageHasColor")
                            mode.ColorFilter(img, FilterData, output, mask);
                        else
                            mode.ColorFilterHSV(img, FilterData, output, mask);

                        if (option2 != "noshow")
                            imshow("Filter Result", output);

                        TotalPixels = img.rows * img.cols;
                        NonZeroPixels = cv::countNonZero(mask);

                        std::cout << "Total pixels: \t" << TotalPixels << endl;
                        std::cout << "Filter Settings B:" << FilterData.B << "\t Green:" << FilterData.G << "\t Red:" << FilterData.R << endl;
                        std::cout << "Found Pixels: " << NonZeroPixels << endl;
                        cv::waitKey(0);
                    }
                    else {
                        std::cout << "Wrong argument setting, example " << endl;
                        std::cout << "imageHasColors [path\\img.ext] [B,G,R,T1,T2,T3] [showResult/noshow]" << endl;
                    }
                }

            }

             else if (ErrCode < 0 && user_operation == "snapshot") {

                std::cout << "Snapshot mode" << endl;
                int cam = 0;
                cam = std::stoi(argv[2], nullptr);

                VideoCapture cap(cam); // Initialize camera
                 // Get the frame
                Mat save_img; cap >> save_img;
                //this_thread::sleep_for(chrono::seconds(3));
                cap >> save_img; //Take snapshot after 3 seconds
                if (save_img.empty()) {
                  std::cerr << "ERROR: Something wrong with Camera, confirm it works" << std::endl;
                }
                // Add system timestamp to img
                mode.addTimeStamp(save_img);
                 // Save the frame into a file
                 cv::imwrite(argv[3], save_img); // Save picture
                 std::cout << "Image Save Successfull" << endl;

              }

             else if (ErrCode < 0 && user_operation == "snapwdelay") {

             std::cout << "Snapshot mode with Cam Init'd delay" << endl;
             int cam = 0, userdelay=0;
             cam = std::stoi(argv[2], nullptr);
             if (argc > 3) // User passed a delay parameter 
             {
                 userdelay = std::stoi(argv[4], nullptr);
             }
             else {
                 userdelay = 1;
             }
             VideoCapture cap(cam); // Initialize camera
              // Get the frame
             Mat save_img; cap >> save_img;
             this_thread::sleep_for(chrono::seconds(userdelay));
             
             cap >> save_img; //Take snapshot after 3 seconds
             if (save_img.empty()) {
                 std::cerr << "ERROR: Something wrong with Camera, confirm it works" << std::endl;
             }
             // Add system timestamp to img
             mode.addTimeStamp(save_img);
             // Save the frame into a file
             cv::imwrite(argv[3], save_img); // Save picture
             std::cout << "Image Save Successfull" << endl;

              }

            else {
                std::cout << "Required Image cannot be loaded, check path" << endl;
                std::cout << "Example: colorfinder.exe [operation] [c:/path/to/image.png]" << endl;
            }
        }
        else {
            if (user_operation == "help") {

                std::cout << "show [c:/path/to/image.png] to display an Image" << endl;
                std::cout << "colorFilter [c:/path/to/image.png] to display a color filter example" << endl;
                std::cout << "pickColor_hover [c:/path/to/image.png] hovering the mouse will display the color value" << endl;
                std::cout << "pickColor_click [c:/path/to/image.png] Click in a region of the image to display the color value" << endl;
                std::cout << "findROI_click" << endl;
                std::cout << "colorFilter_mouse" << endl;
                std::cout << "find_ROI" << endl;
                std::cout << "imageHasColor [c:/path/to/image.png] [B,G,R,TolB,TolG,TolR] [show/noshow] display an image and set up a Color Filter" << endl;
                std::cout << "snapshot [Cam Index 0...9] [c:/path/to/save/image.png] Take a snapshot using the Cam at 0...9" << endl;
                std::cout << "snapwdelay [Cam Index 0...9] [c:/path/to/save/image.png] [delay(seconds)] Take a snapshot using selected cam and wait N seconds" << endl;
            }
            else
            {
                std::cout << "Command Error, Enter help to display list of commands";
                system("pause");
            }

            ErrCode = -1;
        }
   }

    catch (char *e) {
        ErrCode = -150;
   }

    return ErrCode;
}