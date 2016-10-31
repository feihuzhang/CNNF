#ifndef _FEATURE_H
#define _FEATURE_H
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
#include<omp.h>

#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
using namespace cv;
using namespace std;

//#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define PI 3.141592653
struct Layer
{
	int Ksize; //dim1 Ksize*Ksize is the datasize
	int Nin; //dim2
	int Nout; //dim3
	float***weights;
	float*biases;
	
	
};
class Feature
{
public:
	Mat img;
	int *tag;
	float **data;
	int Nlayer;
	int Nlayer1;
	int Nlayer2;
	int NUM_THREADS;
	Layer *Layers;
	Layer *Layers1;
	Layer *Layers2;
	int width;
	int height;
	int channel;
	void LoadFeature(char*filename);
	
	void Initial(int Height,int Width,int Channel);
	void Initial(char*imgname,char*modelname);
	void LoadModel(char*filename);
	void TagAllPixels(char*filename);
	void SaveFeature(char*filename);
	void GetFeature(char*imgname,char*modelname,char*featurename);
	void LinearData(int x,int y,float*rem,int tag);
	void LinearData(float x,int y,float*rem,int tag);
	void LinearData(float x,float y,float*rem,int tag);
	void FreeMem();
	void Extractor();
	void Extractor(vector<Mat> &DataIn,vector<Mat>&DataOut,int i,int j);
	
	

public:
	
	Feature()
	{
		data=NULL;
		tag=NULL;
		Layers=NULL;
		Layers1=NULL;
		Layers2=NULL;
		NUM_THREADS=4;
	}
	~Feature()
	{
		FreeMem();
	}
	
};


#endif
