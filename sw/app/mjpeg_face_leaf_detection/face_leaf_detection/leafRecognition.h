/*
 * LeafRecognition.h
 *
 *  Created on: Jul 21, 2013
 *      Author: Jerry Peng
 */


#ifndef LEAFRECOGNITION_H_
#define LEAFRECOGNITION_H_

#include"opencv2/opencv.hpp"
#include "hullDetector.h"
#include "LeafClassifier.h"
#include <stdio.h>

using namespace cv;

void leafRecognition(Mat *image, Mat* scale8u, char* label, Size2f patchSize);

#endif /* LEAFRECOGNITION_H_ */
