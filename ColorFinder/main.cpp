#include "ColorFinder_Header.h"
#include "OperationModes.h"

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

    OperationModes  mode;
        
        user_operation = argv[1];
        filename = String(argv[2]);
        
        if (user_operation == "show") {

            int ErrCode = mode.loadImage(filename, img);

            if (ErrCode > 0)
                imshow("Image Display", img);
            else
                cout << "Image cannot be loaded, Error code:" << ErrCode << endl;
            waitKey(0);
        }
        else if (user_operation == "colorFilter")
        {
            cv::Mat mask, filterImg;

            int ErrCode = mode.loadImage(filename, img);

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

            int ErrCode = mode.loadImage(filename, img);
            if (ErrCode > 0) {
                //int ColorFilterValues[3] = { 0,255,0 };
                // mode.ColorFilter(img, ColorFilterValues, 40, mask);
                // waitKey(0);
                mode.filename_str = filename;
                //imshow("Press ESC to Exit", img);
                //setMouseCallback("Press ESC to Exit", onMouse());
                mode.PickColor(0);
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

            int ErrCode = mode.loadImage(filename, img);
            if (ErrCode > 0) {
                mode.filename_str = filename;
                mode.PickColor(1);
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
        else
            cout << "Command Error, Enter help to display list of commands";

    return 0;
}