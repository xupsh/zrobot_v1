/*
 * LeafClassifier.h
 *
 *  Created on: Jul 24, 2012
 *      Author: shenyunjun
 */

#ifndef LEAFCLASSIFIER_H_
#define LEAFCLASSIFIER_H_

#include"opencv2/opencv.hpp"

#include "cxcore.h"

class LeafClassifier {
public:
	LeafClassifier();
	virtual ~LeafClassifier();

	//virtual void Train(cv::Mat data, cv::Mat label, cv::Mat variance);
	size_t Predict(float *feature);

private:
	cv::Mat leafData;
	cv::Mat leafVar;

	int typeNum;

	double thresh;


};

#endif /* LEAFCLASSIFIER_H_ */
