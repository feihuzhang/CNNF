#ifndef _SUPERPIXEL_H
#define _SUPERPIXEL_H
#include<iostream>
#include<time.h>
#include<cstring>
#include<string>
#include<cstdio>
#include<math.h>
#include<algorithm>
#include<fstream>
#include<queue>
#include<vector>
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
using namespace cv;
using namespace std;

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define PI 3.141592653


class Image
{
public:
	int **RGB;
	Mat img;
	int height,width;
	float *grad;
	float Sx(float x);
	void BiCubic(float row,float col,float&grad,float *rgb);
public:
	void load(char*filename);
	void Initial(char*filename,bool Stereo);
	void LinearRGB(float x, int y,float*rgb);
	float LinearGrad(float x, int y);
	void FreeMem();
	bool stereo;
public:
	Image()
	{
		RGB=NULL;
		grad=NULL;
		stereo=true;

	}
	~Image()
	{
	
	}
	
};


#endif
