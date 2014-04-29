/*
 * hullDetector.h
 *
 *  Created on: Jul 23, 2012
 *      Author: shenyunjun
 */

#ifndef HULLDETECTOR_H_
#define HULLDETECTOR_H_

//#define DEBUG

#include "cxcore.h"


using namespace cv;

class HullDetector {
public:
	HullDetector();
	virtual ~HullDetector();

public:
	//the process function,
	//input:the contour of the leaf
	//return:	0 success
	//			1 failed
	bool HullProcess(std::vector<Point> contour);

	//calculate the convex hull area
	//input:the point set of hull
	//return:the area of the hull
	double CalculateHullArea(std::vector<Point> hull);

	//calculate the defects in the convex hull
	//the output defects data type is common used   vector<Vec4i> ....
	void ConvexityDefects(InputArray _points, InputArray _hull, OutputArray _defects);

	//calculate the perimeter of the hull
	//input:point set of the hull
	//return: the perimeter of the hull
	double CalculateHullPerimeter(std::vector<Point> hull);

public:
	//getter
	size_t getHullArea();
	size_t getContourArea();
	
	size_t getDefectCnt();
	double getAreaRatio();
	double getPerimeterRatio();
	//setter
	void setThresholdRatio(double _minmaxThreshRatio, double _areaThreshRatio);

private:
	size_t defectCnt;		//the valid count of convex defects
	double contourArea;
	double hullArea;
	double areaRatio;		//the area ratio between convex hull and contour

	double hullPerimeter;
	double contourPerimeter;
	double perimeterRatio;


	double minmaxThreshRatio;
	double areaThreshRatio;


};

#endif /* HULLDETECTOR_H_ */
