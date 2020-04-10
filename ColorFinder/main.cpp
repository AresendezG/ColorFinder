#include "ColorFinder_Header.h"
#include "OperationModes.h"
#include "CustomTypes.h"

using namespace cv;
using namespace std;


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
                mode.ColorFilter(img, ColorFilterValues[0], 40, mask);
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
                        mode.Find_ROI(img, click_data.rectArea);
                        click_data.rectangleSelected = false; //After drawing the ROI, wait for next
                    }
                    //Check next image in the folder
                }

            }
            else
                cout << "Image cannot be loaded, Error Code: " << endl;

        }



        else if (user_operation == "find_ROI") {

            cv::Rect roi;
                roi.x = 200;
                roi.y = 150;
                roi.width = 300;
                roi.height = 200;

            if (ErrCode > 0) {

               mode.Find_ROI(img, roi);
            }
            else
                cout << "Image cannot be loaded, Error Code" << endl;
        }

        else
            cout << "Command Error, Enter help to display list of commands";

    return 0;
}