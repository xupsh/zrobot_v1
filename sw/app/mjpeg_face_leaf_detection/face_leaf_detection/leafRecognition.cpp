#include "leafRecognition.h"

HullDetector Hull;
LeafClassifier Classifier;

int race=0 ;

void leafRecognition(Mat *image, Mat* scale8u, char* label, Size2f patchSize){
  ////切割出树叶区域///////////////////////////////////////////////////////////////////
	  Mat BW2;
	  Mat ROI(*scale8u,Rect(patchSize.width/8,patchSize.height/8, patchSize.width*6/8, patchSize.height*6/8));	
//	  imwrite("/nfs/scale8u_ROI_in.bmp",ROI);
	  threshold( ROI, BW2, 0, 255, CV_THRESH_OTSU+THRESH_BINARY_INV );
  
  // Contour Extract
	  vector<vector<Point> > contours;
	  vector<vector<Point> >::iterator itc;
	  findContours( BW2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
	  int maxSize = 0;
	  itc = contours.begin();
	  while(itc!= contours.end()) {             //find the max contour size
					  if(itc->size() > maxSize)				
						  maxSize = itc->size();
					  ++itc;
		  }
	  itc = contours.begin();
	  while(itc!= contours.end()) {             //Eliminate smaller contours
					  if(itc->size() < maxSize)
						  itc=contours.erase(itc);
					  else
					  ++itc;
		  }
	  Mat BW_CONTOUR(BW2.size(), CV_8U, Scalar(255));
	  drawContours(BW_CONTOUR, contours, -1, Scalar(0), CV_FILLED);
  //	imshow("BW_CONTOUR",BW_CONTOUR);
 //   imwrite("/nfs/BW_CONTOUR.bmp",BW_CONTOUR);

  // Feature Extraction
	  //Min_Rect_extract

  if(contours.size() != 0)
  {
	  itc = contours.begin();
	  RotatedRect rect;
	  rect = minAreaRect(*itc);
	  Point2f vertices[4];
	  rect.points(vertices);
	  int max_x= 0;
	  int min_x= 640;
	  int max_y= 0;
	  int min_y= 480;
	  Point2f P[4];
	  for(int i=0; i<4; i++) {
		  //
		  if(max_x < vertices[i].x) { max_x = vertices[i].x; P[2] = vertices[i]; };
		  if(min_x > vertices[i].x) { min_x = vertices[i].x; P[0] = vertices[i]; };
		  if(max_y < vertices[i].y) { max_y = vertices[i].y; P[3] = vertices[i]; };
		  if(min_y > vertices[i].y) { min_y = vertices[i].y; P[1] = vertices[i]; };
	  }
	  //计算四个象限区域面积
	  float Area[4];
	  float A[4], B[4], C[4];
	  for(int i=0; i<4; i++) {
		  A[i]= 1/(P[(i+1)%4].x-P[i].x);
		  B[i]= 1/(P[i].y-P[(i+1)%4].y);
		  C[i]= P[i].x/(P[i].x-P[(i+1)%4].x)-P[i].y/(P[i].y-P[(i+1)%4].y);
		  Area[i]= 0;
	  }
	  //根据矩行是否垂直，分情况讨论。
	  if(P[0].x==P[1].x || P[0].x==P[3].x) //垂直
		  for(int j=0; j<BW_CONTOUR.rows; j++) {	
			  uchar* data= BW_CONTOUR.ptr<uchar>(j);
			  for(int i=0; i<BW_CONTOUR.cols * BW_CONTOUR.channels(); i++)
				  if(i>min_x && i<(min_x+max_x)/2 && j>min_y && j<(min_y+max_y)/2 && data[i]==0) // 1st quadrant
					  Area[0]++;
				  else if(i>(min_x+max_x)/2 && i<max_x && j>min_y && j<(min_y+max_y)/2 && data[i]==0) // 2nd quadrant
					  Area[1]++;
				  else if(i>min_x && i<(min_x+max_x)/2 && j>(min_y+max_y)/2 && j<max_y && data[i]==0) // 3rd quadrant
					  Area[2]++;
				  else if(i>(min_x+max_x)/2 && i<max_x && j>(min_y+max_y)/2 && j<max_y && data[i]==0) // 4th quadrant
					  Area[3]++;
		  }
	  else   //非垂直
		  for(int j=0; j<BW_CONTOUR.rows; j++) {
			  uchar* data= BW_CONTOUR.ptr<uchar>(j);
			  for(int i=0; i<BW_CONTOUR.cols * BW_CONTOUR.channels(); i++)
				  // 矩形区域： A[0]*i+B[0]*j>-C[0] && A[0]*i+B[0]*j<C[2] &&  A[1]*i+B[1]*j<-C[1] && A[1]*i+B[1]*j>C[3]
				  if(A[0]*i+B[0]*j>-C[0] && A[0]*i+B[0]*j<(C[2]-C[0])/2 && A[1]*i+B[1]*j>C[3] && A[1]*i+B[1]*j<(C[3]-C[1])/2 && data[i]==0) // 1st quadrant
					  Area[0]++;
				  else if(A[0]*i+B[0]*j>-C[0] && A[0]*i+B[0]*j<(C[2]-C[0])/2 && A[1]*i+B[1]*j>(C[3]-C[1])/2 && A[1]*i+B[1]*j<-C[1] && data[i]==0) // 2nd quadrant
					  Area[1]++;
				  else if(A[0]*i+B[0]*j>(C[2]-C[0])/2 && A[0]*i+B[0]*j<C[2] && A[1]*i+B[1]*j>(C[3]-C[1])/2 && A[1]*i+B[1]*j<-C[1] && data[i]==0) // 3rd quadrant
					  Area[2]++;
				  else if(A[0]*i+B[0]*j>(C[2]-C[0])/2 && A[0]*i+B[0]*j<C[2] && A[1]*i+B[1]*j>C[3] && A[1]*i+B[1]*j<(C[3]-C[1])/2 && data[i]==0) // 4th quadrant
					  Area[3]++;
		  }
	  // 象限归一化，长边的一侧是1、2.
	  float L01, L12;
	  L01= sqrt((P[0].x-P[1].x)*(P[0].x-P[1].x)+(P[0].y-P[1].y)*(P[0].y-P[1].y));
	  L12= sqrt((P[1].x-P[2].x)*(P[1].x-P[2].x)+(P[1].y-P[2].y)*(P[1].y-P[2].y));
	  //
	  if(L01<L12){
		  int temp[4];
		  for(int i=0; i<4; i++)
			  temp[i]= Area[i];
		  Area[0]= temp[3];
		  Area[1]= temp[0];
		  Area[2]= temp[1];
		  Area[3]= temp[2];
	  }
	  //
	  float L_ratio, W_ratio;
	  if( (Area[0]+Area[1])>(Area[2]+Area[3]) ) L_ratio= (Area[2]+Area[3])/(Area[0]+Area[1]);
	  else L_ratio= (Area[0]+Area[1])/(Area[2]+Area[3]);
	  //
	  if( (Area[0]+Area[3])>(Area[1]+Area[2]) ) W_ratio= (Area[1]+Area[2])/(Area[0]+Area[3]);
	  else W_ratio= (Area[0]+Area[3])/(Area[1]+Area[2]);
	  //
	  Size2f rectSize; 
	  rectSize = rect.size;
	  float aspectRatio;
	  if(rectSize.height >= rectSize.width){
		  aspectRatio = rectSize.height/rectSize.width;
	  }
	  else{
		  aspectRatio = rectSize.width/rectSize.height;
	  }
	  // Min_Rect_extract_end
	
	  //convexHull

	  if(Hull.HullProcess(*itc));
	  int concave_num= Hull.getDefectCnt();
	  float HullAreaRatio= Hull.getAreaRatio();
	  float HullPerimeterRatio= Hull.getPerimeterRatio();
	

	  // Others
	  float perimeter;
	  float area;
	  Point2f circleCenter;
	  float circleRadius; 
	  Moments mom;
	  double hu[7];
	  float circleFactor;
	  float rectFactor;
	  float psRatio;
	  float curveFactor;
	  mom = moments(Mat(*itc));
	  HuMoments(mom,hu);
	  perimeter = arcLength(*itc,1);						//轮廓周长
	  area = contourArea(*itc);							//轮廓面积
	  minEnclosingCircle(*itc,circleCenter,circleRadius);	//轮廓最小外接圆形
	  circleFactor = 4*3.1415926*area/(perimeter*perimeter);
	  rectFactor = area/(rectSize.height*rectSize.width);
	  psRatio = perimeter/(rectSize.height+rectSize.width);
	  curveFactor = perimeter/circleRadius;

	  // Classifier
	  float feature[11]= {aspectRatio, circleFactor, rectFactor, psRatio, curveFactor,
						  hu[0], HullAreaRatio, HullPerimeterRatio, L_ratio, W_ratio, concave_num};
/*		
		for( int i=0; i<11;i++ ){
		printf("%f,",feature[i]);
		}
		printf("\n");
*/	
	  int Race= 0;
	  Race= Classifier.Predict(feature);
	  if(Race>0 && Race<33){
		  race= Race;
	    // 结果字符串输出
	    int res;
	    res= sprintf(label, "./leafname %d",race);
	    label[res]='\0';
	    //printf("leaf:%s\n",label);
	}
  } //if(contours.size() != 0)_end




  // draw race name
  if(race==1)			putText(*image, "bamboo", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==2)	putText(*image, "Nerium Indcus", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==3)	putText(*image, "Manglietia Fordiana", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==4)	putText(*image, "Amygdalus Persica", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==5)	putText(*image, "Toona Sinensis", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==6)	putText(*image, "Sawtooth oak", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==7)	putText(*image, "Phoebe zhennan", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==8)	putText(*image, "Citrus reticulata Blanco", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);

  else if(race==9)	putText(*image, "Cinnamomum Japonicum", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==10)	putText(*image, "Yulan Magnolia", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==11)	putText(*image, "Aesculus Chinensis", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==12)	putText(*image, "American Elm", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==13)	putText(*image, "Osmanthus Fragrans", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==14)	putText(*image, "Indigofera tinctoria", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==15)	putText(*image, "Juglans mandshurica", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==16)	putText(*image, "Pittosporum Tobira", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==17)	putText(*image, "Prunus Yedoensis", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==18)	putText(*image, "Ginkgo Biloba", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==19)	putText(*image, "Chinese Parasol", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==20)	putText(*image, "Liriodendron Chinense", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==21)	putText(*image, "Lagerstroemia Indica", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==22)	putText(*image, "Mahonia Bealei", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==23)	putText(*image, "Coleus", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==24)	putText(*image, "Mulberry", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==25)	putText(*image, "Populus", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==26)	putText(*image, "Cercis Chinensis", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==27)	putText(*image, "trident maple", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==28)	putText(*image, "Kalopanax Septemlobus", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==29)	putText(*image, "red maple", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==30)	putText(*image, "acer monoes", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==31)	putText(*image, "Sibbaldia procumbens", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);
  else if(race==32)	putText(*image, "Acer palmatum", Point(20,460), FONT_HERSHEY_SIMPLEX, 1.4,Scalar(0,255,0),3,8);

  
}
