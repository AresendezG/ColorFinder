#include "ColorFinder_Header.h"
#include "OperationModes.h"
#include "CustomTypes.h"

using namespace cv;
using namespace std;

/*
    Author: EARG
    ARGE Software, a brand of ARGE Technologies, LLC
    License: 
        Open Source, feel free to copy or reuse this code as you desire. 
        Parts of this code were copied from various OpenCV's ORG own resource pages:
        https://answers.opencv.org/questions/
        https://docs.opencv.org/master/examples.html
        This software has no warranty

*/


//Global Variables
Mat img, placeholder;

// Callback function for any event on he mouse

int main(int argc, const char** argv)
{
    //String filename;
    // Read the input image

    cv::String filename;
    std::string user_operation;
    cv::Mat img;
   // ClickHandler *click_ptr;
    ClickHandler click_data;

    click_data.isDragging = false;
    click_data.isReleased = true;
    click_data.rectangleSelected = false;

    OperationModes  mode;
        
        user_operation = argv[1];
        filename = String(argv[2]);
        

        int ErrCode = mode.loadImage(filename, img);

        if (user_operation == "show") {

            if (ErrCode > 0)
                imshow("Image Display", img);
            else
                cout << "Image cannot be loaded, Error code:" << ErrCode << endl;
            waitKey(0);
        }
        else if (user_operation == "colorFilter")
        {
            cv::Mat mask, filterImg;

            if (ErrCode > 0) {
                double ColorFilterValues[3] = { 118,176,204 };
              //  mode.ColorFilter(img, ColorFilterValues[0], 40, mask);
                imshow("Result Screen", mask);
                waitKey(0);
            }
            else
                cout << "Image cannot be loaded, Error Code: " << endl;
        }
        else if (user_operation == "pickColor_hover")
        {
            //namedWindow("Press ESC to Exit", WINDOW_AUTOSIZE);
            // Create a callback function for any event on the mouse
            if (ErrCode > 0) {
                //int ColorFilterValues[3] = { 0,255,0 };
                // mode.ColorFilter(img, ColorFilterValues, 40, mask);
                // waitKey(0);
                mode.filename_str = filename;
                //imshow("Press ESC to Exit", img);
                //setMouseCallback("Press ESC to Exit", onMouse());

                ClickHandler click;
                mode.PickColor(0, click);
                while (1)
                {
                    //setMouseCallback("Press ESC to Exit", onMouse);
                    char k = waitKey(1) & 0xFF;
                    if (k == 27)
                        break;
                    //Check next image in the folder
                }

            }
            else
                cout << "Image cannot be loaded, Error Code: " << endl;


        }
        else if (user_operation == "pickColor_click") {

            if (ErrCode > 0) {
                ClickHandler click;
                mode.filename_str = filename;
                mode.PickColor(1, click);
                while (1)
                {
                    //setMouseCallback("Press ESC to Exit", onMouse);
                    char k = waitKey(1) & 0xFF;
                    if (k == 27)
                        break;
                    //Check next image in the folder
                }

            }
            else
                cout << "Image cannot be loaded, Error Code: " << endl;

        }


        else if (user_operation == "findROI_click") {

            if (ErrCode > 0) {
                FilterValues FilterData;
                mode.filename_str = filename;
                mode.PickColor(2, click_data); // Set mouse callback and save everything on click data
                while (1)
                {
                    //setMouseCallback("Press ESC to Exit", onMouse);
                    char k = waitKey(1) & 0xFF;
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
            else
                cout << "Image cannot be loaded, Error Code: " << endl;

        }

        else if (user_operation == "colorFilter_mouse") {

            if (ErrCode > 0) {
                Mat filtered_img;
                mode.filename_str = filename;
                mode.PickColor(2, click_data); // Set mouse callback and save everything on click data
                FilterValues FilterData;
                while (1)
                {
                    char k = waitKey(1) & 0xFF;
                    if (k == 27)
                        break;

                    if (click_data.rectangleSelected)
                    {
                        mode.Find_ROI(img, click_data.rectArea, FilterData);
                        click_data.rectangleSelected = false; //After drawing the ROI, wait for next
                        mode.ColorFilter(img, FilterData, filtered_img);
                        imshow("Filtered Colors", filtered_img);
                        waitKey(0);
                        break;
                    }
                    //Check next image in the folder
                }

            }
            else
                cout << "Image cannot be loaded, Error Code: " << endl;
        }


        else if (user_operation == "find_ROI") {

        FilterValues FilterData;
            cv::Rect roi;
                roi.x = 200;
                roi.y = 150;
                roi.width = 300;
                roi.height = 200;

            if (ErrCode > 0) {

               mode.Find_ROI(img, roi,FilterData);
            }
            else
                cout << "Image cannot be loaded, Error Code" << endl;
        }

        else if (user_operation == "imageHasColor") {
                
        // User must pass Color filter as BBB,GGG,RRR max of 255 for each channel
        std::string user_colorfilter;
        FilterValues FilterData;
        user_colorfilter = argv[3];

        int j = 0; int previousFound = 0;
        

        /* Has color BGR and Tolerance level for each channel */

        int filterValues_Array[3] = { 0,0,0 };

        //StringContainer filter_str_array;

        for (std::string::size_type i = 0; i < user_colorfilter.size(); ++i) {
                    
            if (user_colorfilter[i]==44) //Comma delimiter
            {
                filterValues_Array[j] = stoi(user_colorfilter.substr(previousFound, i));
                    if (filterValues_Array[j] > 255)
                        filterValues_Array[j] = 255;
                    if (filterValues_Array[j] < 0)
                        filterValues_Array[j] = 0;
                
                    previousFound = i+1;
                j++;
            }
            if (j == 2) {
               filterValues_Array[j] = stoi(user_colorfilter.substr(previousFound, i));
               break;
            }

        }
        


        }


        else
            cout << "Command Error, Enter help to display list of commands";

    return 0;
}