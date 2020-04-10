#pragma once
#include "ColorFinder_Header.h"
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
};
