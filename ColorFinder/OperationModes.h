#pragma once
#include "ColorFinder_Header.h"


using namespace std;

class OperationModes
{
	public:
		string  filename_str;
		int loadImage(std::string filename_str, cv::Mat &img_mat);
		static void onMouse(int event, int x, int y, int flags, void* userdata);
		void resizeImage(cv::Mat &Image, int Xsize, int Ysize);
		void ColorFilter(cv::Mat& input, double &colorFilterTarget, int Tolerance, cv::Mat& output);
		void PickColor(int mode);
		static void MouseClick(int event, int x, int y, int flags, void* userdata);

	private: 
		cv::String filename_opencvFormat;
		cv::Mat obj_img;
		cv::String windowname;


};

