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


    void OperationModes::onMouse(int event, int x, int y, int flags, void* userdata)
    {
        //cv::Mat img_mat = img;

        //Pass Matrix data as Pointer via userdata
        cv::Mat* pImage = (cv::Mat*) userdata;
        cv::Mat obj_image = *pImage;

        //cv::imread(this->filename_str, 1);

        cv::Mat placeholder_mat;

        if (event == EVENT_MOUSEMOVE)
        {
            //imshow("Image", obj_image);
            Vec3b bgrPixel(obj_image.at<Vec3b>(y, x));

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
            placeholder_mat = Mat::zeros(obj_image.rows, 400, CV_8UC3);

            //fill the placeholder with the values of color spaces
            putText(placeholder_mat, format("BGR [%d, %d, %d]", bgrPixel[0], bgrPixel[1], bgrPixel[2]), Point(20, 70), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("HSV [%d, %d, %d]", hsvPixel[0], hsvPixel[1], hsvPixel[2]), Point(20, 140), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("YCrCb [%d, %d, %d]", ycbPixel[0], ycbPixel[1], ycbPixel[2]), Point(20, 210), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("LAB [%d, %d, %d]", labPixel[0], labPixel[1], labPixel[2]), Point(20, 280), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);


            Size sz1 = obj_image.size();
            Size sz2 = placeholder_mat.size();

            //Combine the two results to show side by side in a single image
            Mat combinedResult(sz1.height, sz1.width + sz2.width, CV_8UC3);
            Mat left(combinedResult, Rect(0, 0, sz1.width, sz1.height));
            obj_image.copyTo(left);
            Mat right(combinedResult, Rect(sz1.width, 0, sz2.width, sz2.height));
            placeholder_mat.copyTo(right);
            imshow("Pick a color to show the ColorVector Info", combinedResult);
        }
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

    void OperationModes::PickColor() {
        /**/

        obj_img = imread(filename_str);
        windowname = "Pick a color to show the ColorVector Info";
        cv::imshow(windowname, obj_img);
        cv::setMouseCallback(windowname, onMouse, &obj_img);
    
    }