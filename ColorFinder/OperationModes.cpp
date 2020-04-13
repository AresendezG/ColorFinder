#include "OperationModes.h"
#include "CustomTypes.h"
#include <fstream>

using namespace cv;

//ClickHandler click;

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
            //Vec3b ycbPixel(ycb.at<Vec3b>(0, 0));
            //Vec3b labPixel(lab.at<Vec3b>(0, 0));

            // Create an empty placeholder for displaying the values
            placeholder_mat = Mat::zeros(obj_image.rows, 400, CV_8UC3);

            //fill the placeholder with the values of color spaces
            putText(placeholder_mat, format("BGR [%d, %d, %d]", bgrPixel[0], bgrPixel[1], bgrPixel[2]), Point(20, 70), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("HSV [%d, %d, %d]", hsvPixel[0], hsvPixel[1], hsvPixel[2]), Point(20, 140), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("Coordinate [X = %d, Y = %d]", x, y), Point(20, 210), FONT_HERSHEY_COMPLEX, .9, Scalar(255, 255, 255), 1);


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


    void OperationModes::ColorFilterHSV(cv::Mat& input, FilterValues& FilterHSV, cv::Mat& output, cv::Mat& mask) {

        double tolerance;

        cv::Scalar lower_color = cv::Scalar(FilterHSV.B - FilterHSV.B_tolerance, FilterHSV.G - FilterHSV.G_tolerance, FilterHSV.R - FilterHSV.R_tolerance);
        cv::Scalar upper_color = cv::Scalar(FilterHSV.B + FilterHSV.B_tolerance, FilterHSV.G + FilterHSV.G_tolerance, FilterHSV.R + FilterHSV.R_tolerance);
        Mat hsv_img;

        cvtColor(input, hsv_img, COLOR_BGR2HSV);
        //imshow("HSV Image", hsv_img0);

        inRange(hsv_img, lower_color, upper_color, mask);

        bitwise_and(hsv_img, hsv_img, output, mask);

        // imshow("Result", output);

    }



    void OperationModes::ColorFilter(cv::Mat& input, FilterValues &FilterData, cv::Mat& output, cv::Mat& mask) {

        // Holds the threshold version of the image:
        //Mat hsv_img0;
        double tolerance;

        // Convert RGB to HSV

      
        cv::Scalar lower_color = cv::Scalar(FilterData.B - FilterData.B_tolerance, FilterData.G - FilterData.G_tolerance, FilterData.R - FilterData.R_tolerance);
        cv::Scalar upper_color = cv::Scalar(FilterData.B + FilterData.B_tolerance, FilterData.G + FilterData.G_tolerance, FilterData.R + FilterData.R_tolerance);

        //Mat mask;
        inRange(input, lower_color, upper_color, mask);

        //imshow("Mask Image", mask);

       // threshold(hsv_img0, mask, 50, 100, THRESH_BINARY);
       // Mat result;

        bitwise_and(input, input, output, mask);

       // imshow("Result", output);

    }

    void OperationModes::PickColor(int mode, ClickHandler &click_data) {
        /**/

        obj_img = imread(filename_str);
        windowname = "Pick a color to show the ColorVector Info";
        cv::imshow(windowname, obj_img);

        switch (mode) {
        case 0:
            cv::setMouseCallback(windowname, onMouse, &obj_img);
            break;
        case 1:
            cv::setMouseCallback(windowname, MouseClick, &obj_img);
            break;
        
        case 2: 
            //ClickHandler click_handle_tmp;
            cv::setMouseCallback(windowname, drawROI_rectangle, &click_data);
            //this->click_handler = click;
        }
    
    }



    void OperationModes::MouseClick(int event, int x, int y, int flags, void* userdata)
    {
        //cv::Mat img_mat = img;

        ofstream logfile;
        
        

        //Pass Matrix data as Pointer via userdata
        cv::Mat* pImage = (cv::Mat*) userdata;
        cv::Mat obj_image = *pImage;

        //cv::imread(this->filename_str, 1);

        cv::Mat placeholder_mat;

        if (event == EVENT_RBUTTONDOWN)
        {
            logfile.open("c:\\users\\esli\\pictures\\logfile.txt", ios::app); //Append to Logfile 
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
            putText(placeholder_mat, format("BGR [%d, %d, %d]", bgrPixel[0], bgrPixel[1], bgrPixel[2]), Point(20, 70), FONT_ITALIC, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("HSV [%d, %d, %d]", hsvPixel[0], hsvPixel[1], hsvPixel[2]), Point(20, 140), FONT_ITALIC, .9, Scalar(255, 255, 255), 1);
            putText(placeholder_mat, format("CRD [X= %d, Y= %d]", x, y), Point(20, 210), FONT_HERSHEY_COMPLEX, .8, Scalar(255, 255, 255), 1);

            logfile << x << "," << y << "," << int(bgrPixel[0]) << "," << int(bgrPixel[1]) << "," << int(bgrPixel[2]) << "\n";

            //std::to_string();

            Size sz1 = obj_image.size();
            Size sz2 = placeholder_mat.size();

            //Combine the two results to show side by side in a single image
            Mat combinedResult(sz1.height, sz1.width + sz2.width, CV_8UC3);
            Mat left(combinedResult, Rect(0, 0, sz1.width, sz1.height));
            obj_image.copyTo(left);
            Mat right(combinedResult, Rect(sz1.width, 0, sz2.width, sz2.height));
            placeholder_mat.copyTo(right);
            imshow("Pick a color to show the ColorVector Info", combinedResult);
       
            logfile.close();
        }

       
    }

    void OperationModes::Find_ROI(cv::Mat &img_mat, cv::Rect &roi, FilterValues &FilterData) {

        ofstream logfile;

        logfile.open("c:\\users\\esli\\pictures\\log.csv", ios::app);

        /* Set Region of Interest */
        cv::Vec3b bgrPixel, hsvPixel; //Pixel handler to log color

        /*
        
            x1,y1 ------ x2,y1
            **           **
            **           **  
            x1,y2 ------ x2,y2 
        */

        /*
        cv::Rect roi;
        roi.x = *ROI_Coordinates[0];
        roi.y = *ROI_Coordinates[1];
        roi.width = *ROI_Coordinates[2] - *ROI_Coordinates[0];
        roi.height = *ROI_Coordinates[3] - *ROI_Coordinates[1];
        */

        /* Crop the original image to the defined ROI */

        //
        cv::Mat crop = img_mat(roi);
        cv::Mat cropHSV;

        cv::imshow("Cropped Image", crop);
        cout << "Selected Area  x1:" << roi.x << "\t y1:" << roi.y << "\t x2:" << roi.x + roi.width << "\t y2:" << roi.y + roi.height << endl;
        OperationModes::getMathData(crop, FilterData);
        cout << endl;

        cv::cvtColor(crop, cropHSV, COLOR_BGR2HSV, 0);
/*
        for (int i = 0; i < crop.rows; i++) {
            for (int j = 0; j < crop.cols; j++) {

                bgrPixel = crop.at<Vec3b>(i, j);
                hsvPixel = cropHSV.at<Vec3b>(i, j);
                logfile<<int(bgrPixel[0])<<","<<int(bgrPixel[1])<< "," <<int(bgrPixel[2])<<","<<int(hsvPixel[0])<<","<<int(hsvPixel[1])<<","<<int(hsvPixel[2])<<","<<i<<","<<j<<endl;
            }
        }
*/
        logfile.close();

        cv::rectangle(img_mat, roi, (0, 255, 0), 1, 8, 0);
        cv::imshow(this->windowname, img_mat);
//        cv::waitKey(0);

        //cv::imwrite("noises_cropped.png", crop);

    }

    void OperationModes::getHistogram(cv::Mat& hist_src) {

        vector<Mat> bgr_planes;
        // Split the region of interest on Blue Green & Red (bgr) planes
        split(hist_src, bgr_planes);
        int histSize = 256;
        float range[] = { 0, 256 }; //the upper boundary is exclusive, bgr values can be 0 to 255 
        const float* histRange = { range };
        bool uniform = true, accumulate = false; 
        
        Mat b_hist, g_hist, r_hist;
        calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
        int hist_w = 512, hist_h = 400;
        int bin_w = cvRound((double)hist_w / histSize);
        Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
              
        for (int i = 1; i < histSize; i++)
        {
            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
                Scalar(255, 0, 0), 2, 8, 0);
            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
                Scalar(0, 255, 0), 2, 8, 0);
            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
                Scalar(0, 0, 255), 2, 8, 0);
        }
        //imshow("Source image", src);
        imshow("calcHist Demo", histImage);
        waitKey();

    }

    void OperationModes::getMathData(cv::Mat& src, FilterValues &bgr_filter) {

        vector<Mat> bgr_planes;

        split(src, bgr_planes);

        Scalar std_dev;
        Scalar data_mean;

        int histSize = 256;
        float range[] = { 0, 256 }; //the upper boundary is exclusive, bgr values can be 0 to 255 
        const float* histRange = { range };
        bool uniform = true, accumulate = false;

        double std_dev_array[3];
        double mean_array[3];
        double range_array[3];
        double min, max;
        int minIndex, MaxIndex;

        /* Get RGB Histogram to find most common RGB values on the ROI */

        Mat b_hist, g_hist, r_hist;
        calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
        calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
        int hist_w = 512, hist_h = 400;
        int bin_w = cvRound((double)hist_w / histSize);
        Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());



        for (int i = 0; i < 3; i++) {
            cv::meanStdDev(bgr_planes[i], data_mean, std_dev, noArray());
            cv::minMaxIdx(bgr_planes[i], &min, &max, &minIndex, &MaxIndex, noArray());
            std_dev_array[i] = std_dev.val[0];
            mean_array[i] = data_mean[0];
            range_array[i] = max - min;
        }

        cv::minMaxIdx(b_hist, &min, &max, &minIndex, &MaxIndex, noArray());
            //mode_array[0] = MaxIndex;
            bgr_filter.B = MaxIndex;
        cv::minMaxIdx(g_hist, &min, &max, &minIndex, &MaxIndex, noArray());
            //mode_array[1] = MaxIndex;
            bgr_filter.G = MaxIndex;
        cv::minMaxIdx(r_hist, &min, &max, &minIndex, &MaxIndex, noArray());
            //mode_array[2] = MaxIndex;
              bgr_filter.R = MaxIndex;

        cout << "Blue: \t std " << std_dev_array[0] << "\t mean: " << data_mean[0] << "\t range: " << range_array[0] <<"\t mode:"<<bgr_filter.B << endl;
        cout << "Green: \t std " << std_dev_array[1] << "\t mean: " << data_mean[1] << "\t range: " << range_array[1] << "\t mode:" << bgr_filter.G << endl;
        cout << "Red: \t std " << std_dev_array[1] << "\t mean: " << data_mean[2] << "\t range: " << range_array[2] << "\t mode:" << bgr_filter.R << endl;

        bgr_filter.B_tolerance = std_dev_array[0];
        bgr_filter.G_tolerance = std_dev_array[1];
        bgr_filter.R_tolerance = std_dev_array[2];
        
        MaxIndex = 0;
        minIndex = 0;
    }

    void OperationModes::findROI_click(cv::Mat &img_mat){
    
    }

    void OperationModes::drawROI_rectangle(int event, int x, int y, int flags, void* userdata){

        ClickHandler* pHandler = (ClickHandler*) userdata;
        ClickHandler handler = *pHandler;

            if (event == EVENT_LBUTTONDOWN && handler.isDragging == false)
            {
                //keep track of initial point clicked
                handler.startPoint= cv::Point(x, y);
                //user has begun dragging the mouse
                handler.isDragging = true;
                //copyback to handler
                *pHandler = handler;
            }
            /* user is dragging the mouse */
            if (event == EVENT_MOUSEMOVE && handler.isDragging == true)
            {
                //keep track of current mouse point
                handler.currentPoint = cv::Point(x, y);
                //user has moved the mouse while clicking and dragging
                handler.isMoving = true;
                *pHandler = handler;
            }
            /* user has released left button */
            if (event == EVENT_LBUTTONUP && handler.isDragging == true)
            {
                //set rectangle ROI to the rectangle that the user has selected
                handler.rectArea = Rect(handler.startPoint, handler.currentPoint);

                //reset boolean variables
                handler.isDragging = false;
                handler .isMoving = false;
                handler.isReleased = true;
                handler.rectangleSelected = true;
                *pHandler = handler;
            }

            if (event == EVENT_RBUTTONDOWN) {
                //user has clicked right mouse button
                //Reset HSV Values
               // handler.isDragging = true;

            }


    }
