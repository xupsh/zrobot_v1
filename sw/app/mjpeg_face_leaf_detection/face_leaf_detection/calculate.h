#ifndef CALCULATE
#define CALCULATE


#include "opencv2/opencv.hpp"
#include "math.h"
#include <stdio.h>

using namespace cv;

class Calculate {
	private:

  int Match(Mat UniChar, Mat temp);

  int NumClassifier(Mat charImage, Rect charArea);

  int OperateClassifier(Mat charImage, Rect charArea);

  public:
	   //constructor
	    Calculate(){};
	  //destructor
	    ~Calculate(){};

  void Recognition(Mat *image, Mat* scale8u, char* label, Size2f patchSize);
};

#endif
