#ifndef COST_FILTER_H
#define COST_FILTER_H
#define _IMPROVED 0
#include "guidedfilter.h"
#include "Image.h"

//class GuidedFilterImpl;

class CostFilter
{

public:
	int height;
	int width;
	float thresh;
	float MaxU,MaxV,MinU,MinV;
	float precision;
	Image img1;
	Image img2;
	float**data1;
	float**data2;
	float eps;
	int radius;
//	float**data1;
//	float**data2;
	int channel;
	float step;
	bool stereo;
public:
    CostFilter()
	{
			thresh=2;
			radius=9;
			eps=0.01*255*255;
			step=1;
			precision=1;
			//MaxMotion=220;
			stereo=true;
			
	}
    ~CostFilter()
	{}
public:
	void Initial(char*filename1,char*filename2,int Stereo,float MaxMotion,int Radius=9,float Eps=0.05);
	void Matching();
	void LoadFeature(char*filename1,char*filename2);
	float PixelCost(int row, int col,float u,float v);
	
	void LinearData(float**data,float row,float col,float*&rem,int tag);
	void LoadData(float**&data,char*filename);

    //cv::Mat filter(const cv::Mat &p, int depth = -1) const;


};
#endif
