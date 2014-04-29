#include "calculatorORleaf.h"

using namespace cv;

#define gray_thres 40		// ÐÎÌ¬Ñ§ÌÝ¶ÈÍŒÏñ¶þÖµ»¯ãÐÖµ
// ·œ¿ò²ÎÊý
#define range 0.10	
#define rectFactor_s 0.95	
// ËãÊœ·œ¿ò²ÎÊý
#define aspectRatio_s_calculate 0.355	
// Ê÷Ò¶·œ¿ò²ÎÊý
#define aspectRatio_s_leaf 0.954

//
Calculate calculate;



int calculatorORleaf(Mat* image, char* label){
  // Structure Define ////////////////////////////////////////////////////////////////
  Mat GRAY;
  Mat GRADIENT;
  Mat element3(3,3,CV_8U,Scalar(1));
  Mat BW;
  vector<vector<Point> > contours;
  vector<vector<Point> >::iterator itc;

  //È«ŸÖ±äÁ¿  0:ÈËÁ³ 1:ËãÊœ 2:Ê÷Ò¶
  int detect_flag= 0; 

  ////ÍŒÏñÔ€ŽŠÀí///////////////////////////////////////////////////////////////////////
  cvtColor(*image, GRAY, CV_RGB2GRAY);
  morphologyEx(GRAY,GRADIENT,MORPH_GRADIENT,element3);
  threshold( GRADIENT, BW, gray_thres, 255, THRESH_BINARY );
  
  
 // imwrite("/nfs/GRAY.bmp",GRAY);
  ////Ñ°ÕÒËãÊœÇøÓò·œ¿ò¡ª¡ªÕÒ×îŽóÏàËÆÂÖÀª//////////////////////////////////////////////
  findContours(BW, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
  itc = contours.begin();
  //find the similar rect
  while(itc!= contours.end()) {             
	  //ÑéÖ€ÊÇ·ñÎªËãÊœ·œ¿ò
	  RotatedRect rect_t;
	  float rectFactor;
	  rect_t= minAreaRect(*itc);
	  // rectFactorŒÆËã
	  rectFactor= contourArea(*itc)/(rect_t.size.width*rect_t.size.height);
	  // È¥³ý²»ÊÇ·œ¿òµÄÂÖÀª
	  if(!(rectFactor>rectFactor_s ))
		  itc=contours.erase(itc);
	  else
	  itc++;
  }

  // Ã»ÓÐŒì²âµœ·œ¿ò
  itc = contours.begin();
  if(itc== contours.end()) return 0;
  // ÕÒµœ×îŽó·œ¿òÂÖÀª
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
	
  // detect_flag ÅÐ¶Ï·œ¿òÀàÐÍ
  itc = contours.begin();
  RotatedRect rect_t;
  rect_t= minAreaRect(*itc);
  float aspectRatio;
  // aspectRatioŒÆËã
  if((rect_t.size.height) < (rect_t.size.width)){aspectRatio = rect_t.size.height/rect_t.size.width;}
  else{aspectRatio = rect_t.size.width/rect_t.size.height;}
  
  //printf("aspectRatio= %f\n", aspectRatio);
  
  //·œ¿òÅÐ¶Ï
  if(aspectRatio>aspectRatio_s_calculate-range/2 && aspectRatio<aspectRatio_s_calculate+range/2 )
	  detect_flag= 1;
  else if(aspectRatio>aspectRatio_s_leaf-range/2 && aspectRatio<aspectRatio_s_leaf+range/2 )
	  detect_flag= 2;
  else
	  detect_flag= 0;
	  
//	  printf("detect_flag= %d\n", detect_flag);
	  
  if(detect_flag==0) return 0;

  ////·Öžî³öÑ°ÕÒËãÊœ·œ¿òÇøÓò£¬²¢Íê³ÉÍŒÏñÐý×ª//////////////////////////////////////////////
  itc = contours.begin();
  if(itc != contours.end()){
	  RotatedRect rect;
	  rect = minAreaRect(*itc);
	  //
	  Size bounding;  // rect ÍâÂÖÀªÐ£ÕýºóµÄ³ßŽçŽóÐ¡£šwidth > height£©
	  if(rect.boundingRect().size().width > rect.boundingRect().size().height){
		  bounding.width = rect.boundingRect().size().width;
		  bounding.height = rect.boundingRect().size().height;
	  }
	  else{
		  bounding.width = rect.boundingRect().size().height;
		  bounding.height = rect.boundingRect().size().width;
	  }

	  Size2f Rrect;	// rect Ð£ÕýºóµÄ³ßŽçŽóÐ¡£šwidth > height£©
	  if(rect.size.width > rect.size.height){
		  Rrect.width = rect.size.width;
		  Rrect.height = rect.size.height;
	  }
	  else{
		  Rrect.width = rect.size.height;
		  Rrect.height = rect.size.width;
	  }
	  //
	  Mat rotate8u= Mat(rect.boundingRect().size(),CV_8UC1);
	  Mat after_rotate8u =Mat(bounding,CV_8UC1,Scalar(255));
	  getRectSubPix( GRAY, rect.boundingRect().size(),rect.center, rotate8u);
	  //
	  Point2f rotateCenter = Point2f(rect.boundingRect().size().width/2.0 , rect.boundingRect().size().height/2.0);
	  float rotateAngle;
	  Size2f patchSize;
	  //
	  patchSize.width= Rrect.width;
	  patchSize.height= Rrect.height;

	  // ·œ¿òÇãÐ±·œÎ»ÅÐ¶Ï
	  Point2f vertices[4];
	  rect.points(vertices);

	  Point2f up;
	  int miny = 480;
	  up = vertices[3];
	  for(int i=0;i<4;i++){
		  if(vertices[i].y<miny){
			  up = vertices[i];
			  miny = vertices[i].y;
		  }
	  }
	  if(up.x < rect.center.x) rotateAngle= rect.angle + 90;
	  else rotateAngle= rect.angle;
	
	  Mat rotateM = getRotationMatrix2D(rotateCenter, rotateAngle, 1);
	  //warpAffine( rotate8u, after_rotate8u, rotateM, bounding, INTER_LINEAR, BORDER_CONSTANT, 0);
//  imwrite("/nfs/rotate8u.bmp",rotate8u);
//	  imwrite("/nfs/after_rotate8u.bmp",after_rotate8u);
    
    
	  Mat scale8u;
	  ///////////////////////////////////////////////////////////////////
	  // code change here to go across "warpAffine()" BUG
	  ///////////////////////////////////////////////////////////////////
	  getRectSubPix(rotate8u, patchSize, rotateCenter, scale8u);
	  
    
 //   imwrite("/nfs/scale8u.bmp",scale8u);
	
	  // ·œ¿òÇøÓò¹ýÐ¡£¬²»œøÐÐËãÊœ¡¢Ê÷Ò¶Ê¶±ð
	  if(patchSize.width<16 || patchSize.height<16) return 0;

	  //·œ¿òÌõŒþÂú×ã£¬œøÐÐËãÊœ¡¢Ê÷Ò¶Ê¶±ð//////////////////////////////
	  //
	  //ËãÊœ
	  if(detect_flag==1)
		  calculate.Recognition(image, &scale8u, label, patchSize);
	  else if(detect_flag==2){
		  leafRecognition(image, &scale8u, label, patchSize);
  //    imwrite("/nfs/scale8u_out.bmp",scale8u);
      }
	  return 1;
  }
}
