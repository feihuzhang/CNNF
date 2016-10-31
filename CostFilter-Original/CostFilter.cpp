#include"CostFilter.h"

float CostFilter::PixelCost(int row, int col,float u,float v)
{
	float *rem=new float[channel];
	float tag=data1[row*width+col][0];
	if(row+u>=0&&col+v>=0&&col+v<=width-1&&row+u<=height-1)
	{
		LinearData(data2,row+u,col+v,rem,tag);
	}
   else
	{
		for(int k=0;k<channel;k++)
			rem[k]=1.0/sqrt((double)channel);
	}
	float norm1=1e-6;
	float norm2=1e-6;
	int base=1;
	if (tag<0)
		base=channel+1;
	 for(int k=0;k<channel;k++)
	{
		norm1+=pow((float)data1[row*width+col][k+base],2.0);
		norm2+=pow((float)rem[k],2.0);
	}
	norm1=sqrt(norm1);
	norm2=sqrt(norm2);
	float error=0;
	for(int k=0;k<channel;k++)
		error+=pow((float)(data1[row*width+col][k+base]/norm1-rem[k]/norm2),2.0);
	delete[] rem;
 
	return error;
}

void CostFilter::LinearData(float**data,float row,float col,float*&rem,int tag)
{
	//int channel=64;
	float x=col;
	float y=row;
	
	if (x<0||y<0||x>width-1||y>height-1)
	{
		std::cout<<x<<'	'<<y<<std::endl;
		std::cout<<width<<' '<<height<<std::endl;
		std::cout<<"error! LinearData!!"<<std::endl;
		//system("pause");
		exit(0);
	}
	int base=1;
	if(tag>0)
		base=1;
	else
		base=channel+1;
	if(x-(int)x<1e-6&&y-(int)y<1e-6)
	{
		int location=(row*width+col);
		for(int k=base;k<channel+base;k++)
		{
			rem[k-base]=data[location][k];
		}
	}
	else{
	float weight[4];
	int location[4];
	int y1=(int )y;
	int y2=(int)y+1<height-1?(int)y+1:height-1;
	int x1=(int )x;
	int x2=width-1<(int)x+1?width-1:(int)x+1;
	weight[0]=(x2-x)*(y2-y);weight[1]=(x-x1)*(y2-y);
	weight[2]=(x2-x)*(y-y1);weight[3]=(x-x1)*(y-y1);
	location[0]=y1*width+x1;location[1]=y1*width+x2;
	location[2]=y2*width+x1;location[3]=y2*width+x2;
	for(int k=base;k<channel+base;k++)
	{
		rem[k-base]=data[location[0]][k]*weight[0]+data[location[1]][k]*weight[1]+data[location[2]][k]*weight[2]+data[location[3]][k]*weight[3];
	}
	
	}
}
void CostFilter::LoadFeature(char*filename1,char*filename2)
{
	LoadData(data1,filename1);
	LoadData(data2,filename2);
}
void CostFilter::LoadData(float**&data,char*filename)
{
	int temp;
	FILE*fp;
	fp=fopen(filename,"rb");
	if(!fp)
	{
		std::cout<<"Cannot open the file "<<filename<<endl;
		exit(0);
	}
	fread(&temp,sizeof(int),1,fp);
	if(height!=(int)temp)
	{
		std::cout<<"Feature data are inconsistent with the image."<<endl;
		cout<<height<<'	'<<temp<<endl;
		exit(0);
	}
	fread(&temp,sizeof(int),1,fp);
	if(width!=(int)temp)
	{
		cout<<width<<'	'<<temp<<endl;
		std::cout<<"Feature data are inconsistent with the image."<<endl;
		exit(0);
	}
	fread(&channel,sizeof(float),1,fp);
	data=new float*[width*height];
	
	for(int i=0;i<width*height;i++)
		data[i]=new float[channel*2+1];
	for(int row=0;row<height;row++)
	{
		for(int col=0;col<width;col++)
		
		{
			int location=row*width+col;
			
			fread(data[location],sizeof(float),channel*2+1,fp);
			//fread(pLine,sizeof(double),nCols,fp);
		}
	}
}

void CostFilter::Initial(char*filename1,char*filename2,int Stereo,float MaxMotion,int Radius,float Eps)
{
	if(Stereo>=1)
	{
		stereo=true;
		MaxU=MinU=0;
		if(MaxMotion>=0)
		{
			MaxV=0;
			MinV=-MaxMotion;
			//Match.MinV=0;
		}
		else
		{
			MaxV=-MaxMotion;
			MinV=0;
		}
	}
	else
	{
		stereo=false;
		MaxU=MaxV=fabs(MaxMotion);
		MinU=MinV=-fabs(MaxMotion);
	//	MaxU=1;
	//	MinU=-1;
		
	}
		
	img1.Initial(filename1,stereo);

	img2.Initial(filename2,stereo);
	eps=(Eps*255)*(Eps*255);
	radius=Radius;
	//cout<<"Initial OK"<<endl;
	width=img1.width;
	height=img1.height;
}
void CostFilter::Matching()
{ 
	
//	sprintf(filename,"%s%d.png",path,i-1);
	
//	Img.initial("ALL-2views/midd2/view1.png");
	
	
	
	float *resultu=new float[width*height];
	float *resultv=new float[width*height];

	float *rem=new float[width*height];
	for(int i=0;i<width*height;i++)
	{	
			rem[i]=1e10;
			//resultu[i]=max_disp*10;
			//resultv[i]=max_disp*10;
	}

	float alph=0.9;
	//cout<<"OK"<<endl;
	Mat cost(height, width, CV_32FC1);
	for(float u=MinU;u<=MaxU;u+=step)
	{
		for(float v=MinV;v<=MaxV;v+=step)
		{
			for(int row=0;row<height;row++)
			{
				for(int col=0;col<width;col++)
				{
				#if _IMPROVED
					cost.at<float>(row,col)=PixelCost(row,col,u,v);
				#else
					float location2=col+v;
					float location1=row+u;
					float tmep1=0,temp2=0;
					float rgb2[3],rgb1[3],grad1,grad2;
					if(location1<=0||location1>=height-1||location2<=0||location2>=width-1)
					{
						rgb2[0]=0.1*255;
						rgb2[1]=0.1*255;
						rgb2[2]=0.1*255;
						grad2=2;
					}
					else
					{
						img2.BiCubic(location1,location2,grad2,rgb2);
				
					}
					float temp1=0;
					for(int dim=0;dim<3;dim++)
					{
						temp1+=fabs(img1.RGB[row*width+col][dim]-rgb2[dim]);
					}
					float temp=(1-alph)*min(temp1,10)+alph*min(fabs(img1.grad[row*width+col]-grad2),2.0);
	
					cost.at<float>(row,col)=temp;
					
					#endif
				}
			}
		//	cout<<u<<'	'<<v<<endl;
			Mat dst=guidedFilter(img1.img, cost, radius, eps);
		//	Mat dst;
		//	ximgproc::guidedFilter(img1.img,cost,dst,radius,eps);
			
		//	cout<<u<<'	'<<v<<endl;
		
			for(int i=0;i<width*height;i++)
			{
				if(rem[i]>dst.at<float>(i/width,i%width))
				{
					rem[i]=dst.at<float>(i/width,i%width);
					resultu[i]=u;
					resultv[i]=v;
				}
			}
		}
	}
	if(stereo)
	{
		Mat save(height,width,CV_16UC1);
		for(int row=0;row<height;row++)
		{
			for(int col=0;col<width;col++)
			{
				save.at<unsigned short>(row,col)=(unsigned short)(fabs(resultv[row*width+col])*256+0.5);
			}
		}
		imwrite("disp.png",save);
	}
	else
	{
		Mat R(height,width,CV_16UC1);
		Mat G(height,width,CV_16UC1);
		Mat B(height,width,CV_16UC1);
		Mat save;
		vector<Mat>temp;

		

		for(int row=0;row<height;row++)
		{
			for(int col=0;col<width;col++)
			{
				B.at<unsigned short>(row,col)=(unsigned short)(resultu[row*width+col]*64)+pow(2.0,15);
				G.at<unsigned short>(row,col)=(unsigned short)(resultv[row*width+col]*64)+pow(2.0,15);
				R.at<unsigned short>(row,col)=1;

			}
		}
		temp.push_back(R);
		temp.push_back(G);
		temp.push_back(B);
		cv::merge(temp, save);
		imwrite("flow.png",save);
	}
}
