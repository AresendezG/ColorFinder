#include "ColorFinder_Header.h"
#include "OperationModes.h"

using namespace cv;
using namespace std;


//Global Variables
Mat img, placeholder;

// Callback function for any event on he mouse

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    cv::Mat img_mat = img; 

    //cv::imread(this->filename_str, 1);

    cv::Mat placeholder_mat;

    if (event == EVENT_MOUSEMOVE)
    {
        imshow("Image",img);
        Vec3b bgrPixel(img.at<Vec3b>(y, x));

        Mat3b hsv, ycb, lab;
        // Create Mat object from vector since cvtColor accepts a Mat object
        Mat3b bgr(bgrPixel);

        //Convert the single pixel BGR Mat to other formats
        cvtColor(bgr, ycb, COLOR_BGR2YCrCb);
        cvtColor(bgr, hsv, COLOR_BGR2HSV);
        cvtColor(bgr, lab, COLOR_BGR2Lab);

        //Get back the vector from Mat
        Vec3b hsvPixel(hsv.at<Vec3b>(0, 0));
        Vec3b ycbPixel(ycb.at<Vec3b>(0, 0));
        Vec3b labPixel(lab.at<Vec3b>(0, 0));

        // Create an empty placeholder for displaying the values
        placeholder_mat = Mat::zeros(img.rows, 400, CV_8UC3);

        //fill the placeholder with the values of color spaces
        putText(placeholder_mat, format("BGR [%d, %d, %d]", bgrPixel[0], bgrPixel[1], bgrPixel[2]), Point(20, 70), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
        putText(placeholder_mat, format("HSV [%d, %d, %d]", hsvPixel[0], hsvPixel[1], hsvPixel[2]), Point(20, 140), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
        putText(placeholder_mat, format("YCrCb [%d, %d, %d]", ycbPixel[0], ycbPixel[1], ycbPixel[2]), Point(20, 210), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
        putText(placeholder_mat, format("LAB [%d, %d, %d]", labPixel[0], labPixel[1], labPixel[2]), Point(20, 280), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);


        Size sz1 = img.size();
        Size sz2 = placeholder_mat.size();

        //Combine the two results to show side by side in a single image
        Mat combinedResult(sz1.height, sz1.width + sz2.width, CV_8UC3);
        Mat left(combinedResult, Rect(0, 0, sz1.width, sz1.height));
        img.copyTo(left);
        Mat right(combinedResult, Rect(sz1.width, 0, sz2.width, sz2.height));
        placeholder_mat.copyTo(right);
        imshow("Pick the color to display RGB Value", combinedResult);
    }
}



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
                int ColorFilterValues[3] = { 0,255,0 };
                mode.ColorFilter(img, ColorFilterValues, 40, mask);
                waitKey(0);
            }
            else
                cout << "Image cannot be loaded, Error Code: " << endl;
        }
        else if (user_operation == "pickColor")
        {
            namedWindow("Press ESC to Exit", WINDOW_AUTOSIZE);
            // Create a callback function for any event on the mouse
          

            int ErrCode = mode.loadImage(filename, img);

            if (ErrCode > 0) {
               //int ColorFilterValues[3] = { 0,255,0 };
               // mode.ColorFilter(img, ColorFilterValues, 40, mask);
               // waitKey(0);
                mode.filename_str = filename;      
                
                imshow("Press ESC to Exit", img);
                setMouseCallback("Press ESC to Exit", onMouse());

 
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

    return 0;
}