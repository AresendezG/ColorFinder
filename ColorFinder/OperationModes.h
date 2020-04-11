#pragma once
#include "ColorFinder_Header.h"
#include "CustomTypes.h"


using namespace std;

class OperationModes
{
	public:
		/*Attributes*/
		string  filename_str;
		//ClickHandler click_data;
		/*Methods*/
		int loadImage(std::string filename_str, cv::Mat &img_mat);
		static void onMouse(int event, int x, int y, int flags, void* userdata);
		void resizeImage(cv::Mat &Image, int Xsize, int Ysize);
		void ColorFilter(cv::Mat& input, FilterValues &FilterData, cv::Mat& output, cv::Mat &mask);
		void PickColor(int mode, ClickHandler &click_data);
		static void MouseClick(int event, int x, int y, int flags, void* userdata);
		void Find_ROI(cv::Mat &img_mat, cv::Rect &roi, FilterValues &FilterData);
		void findROI_click(cv::Mat &img_mat);

	private: 
		/*Attributes*/
		cv::String filename_opencvFormat;
		cv::Mat obj_img;
		cv::String windowname;
		//FilterValues bgr_filterValue;

		/*Methods*/
		void getHistogram(cv::Mat &hist_src);
		void getMathData(cv::Mat &src, FilterValues &FilterData);
		static void drawROI_rectangle(int event, int x, int y, int flags, void* userdata);

};

