#pragma once
#include <string.h>
//#include "ColorFinder_Header.h"
using namespace cv;

struct ClickHandler
{
	Mat img;
	Point startPoint;
	Point endPoint;
	Point currentPoint;
	Rect rectArea;
	bool isDragging;
	bool isReleased;
	bool isMoving;
	bool rectangleSelected;
};

struct FilterValues {
	int B;
	int G;
	int R;
	int B_tolerance;
	int G_tolerance;
	int R_tolerance;
};

struct StringContainer {
	std::string B_str;
	std::string G_str;
	std::string R_str;
};