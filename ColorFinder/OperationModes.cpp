#include "OperationModes.h"

using namespace cv;





	int OperationModes::loadImage(std::string filename_str, cv::Mat &img_mat)
	{
        //cv::Mat LocalMat;
        cv::String filename_opencvFormat;
		filename_opencvFormat = cv::String(filename_str);
		img_mat = cv::imread(filename_opencvFormat, 1);

        if (img_mat.empty())
        {
            return -1;
        }
        else
            return 1;


	}

 
    void OperationModes::resizeImage(cv::Mat &Image, int Xsize, int Ysize) {
        // Resize an Image to the input parameters
        //Pass X size and Y size

        // Resize the image to 400x400
        cv::Size rsize(Xsize, Ysize);
        resize(Image, Image, rsize);

    }



    void OperationModes::ColorFilter(cv::Mat& input, int colorFilterTarget[3], int Tolerance, cv::Mat& output) {

        // Holds the threshold version of the image:
        Mat hsv_img0;

        // Convert RGB to HSV

        cvtColor(input, hsv_img0, COLOR_BGR2HSV);

        imshow("HSV Image", hsv_img0);

        cv::Scalar lower_color = cv::Scalar(colorFilterTarget[0]-(Tolerance/2), colorFilterTarget[1]-(Tolerance/2), colorFilterTarget[2]-(Tolerance/2));
        cv::Scalar upper_color = cv::Scalar(colorFilterTarget[0] + (Tolerance / 2), colorFilterTarget[1] + (Tolerance / 2), colorFilterTarget[2] + (Tolerance / 2));

        Mat mask;
        inRange(input, lower_color, upper_color, mask);

        //threshold(img0, th_img0, 50, 100, THRESH_BINARY);
        // Show the mask
        imshow("Mask ", mask);

        //bitwise opperation to mask the original image
        Mat result;

        bitwise_and(input, input, result, mask);

        imshow("Result", result);


    }
