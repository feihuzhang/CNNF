#include "Image.h"
void Image::LinearRGB(float x, int y,float*rgb)
{
	if (x<0||y<0||x>width-1||y>height-1)
	{
		cout<<"error! LinearRGB!!"<<endl;
		system("pause");
		exit(0);
	}

	float temp[2];
	for(int k=0;k<3;k++)
	{
		temp[0]=(float)RGB[y*width+(int)x][k];
		if((int)x+1>width-1)
			temp[1]=0;
		else
			temp[1]=(float)RGB[y*width+(int)x+1][k];
		rgb[k]=temp[0]*((int)x+1-x)+temp[1]*(x-(int)x);
		
	}
}
float Image::LinearGrad(float x, int y)
{
	if (x<0||y<0||x>width-1||y>height-1)
	{
		cout<<"error! LinearRGB!!"<<endl;
		system("pause");
		exit(0);
	}

	float temp[2];
	
		temp[0]=grad[y*width+(int)x];
		if((int)x+1>width-1)
			temp[1]=0;
		else
			temp[1]=grad[y*width+(int)x+1];
		float g=temp[0]*((int)x+1-x)+temp[1]*(x-(int)x);
		return g;
		
	
}
void Image::load(char *filename )
{
	
	img=imread(filename);
	width=img.size().width;
	height=img.size().height;
	//cout<<width<<' '<<height<<endl;
	
	unsigned int temp=0;
	
	RGB=new int*[width*height];
	grad=new float[width*height];
	Mat grey;
	cvtColor(img,grey,CV_BGR2GRAY);
	Mat sobel;
	//Sobel(
	//Sobel(grey,sobel,CV_64F,1,0,1,0.5);
	if(stereo)
		Sobel(grey,sobel,CV_32FC1,1,1);
	else
		Sobel(grey,sobel,CV_32FC1,1,0);
	for(int row=0;row<height;row++)
		for(int col=0;col<width;col++)
		{
			RGB[row*width+col]=new int[3];

			RGB[row*width+col]=new int[3];
			RGB[row*width+col][0]=(int)img.at<Vec3b>(row,col)[0];
			RGB[row*width+col][1]=(int)img.at<Vec3b>(row,col)[1];
			RGB[row*width+col][2]=(int)img.at<Vec3b>(row,col)[2];
			grad[row*width+col]=sobel.at<float>(row,col);
			
		}

}
void Image::Initial(char*filename,bool Stereo)
{
	stereo=Stereo;
	
	load(filename);
	

}
void Image::BiCubic(float row,float col,float&Grad,float *rgb)
{
	
	int cc,rr;
	int r=(int)row;
	int c=(int)col;
	float u=row-r;
	float v=col-c;
	float A[4],B[4][4],C[4];
	A[0]=Sx(u+1);
	A[1]=Sx(u);
	A[2]=Sx(1-u);
	A[3]=Sx(2-u);
	C[0]=Sx(v+1);
	C[1]=Sx(v);
	C[2]=Sx(1-v);
	C[3]=Sx(2-v);
	for(int k=0;k<3;k++)
	{
		for(int i=-1;i<=2;i++)
		{
			for(int j=-1;j<=2;j++)
			{
				cc=c+j;
				rr=r+i;
				if(cc<0||cc>width-1||rr<0||rr>height-1)
					B[i+1][j+1]=0;
				else
					B[i+1][j+1]=RGB[rr*width+cc][k];
			}
		}
		float sum=0;
		float result=0;
		for(int j=0;j<4;j++)
		{
			sum=0;
			for(int i=0;i<4;i++)
			{
				sum+=A[i]*B[i][j];
			}
			result+=sum*C[j];
		}
		rgb[k]=result;
		
	}
	for(int i=-1;i<=2;i++)
	{
		for(int j=-1;j<=2;j++)
		{
			cc=c+j;
			rr=r+i;
			if(cc<0||cc>width-1||rr<0||rr>height-1)
				B[i+1][j+1]=0;
			else
				B[i+1][j+1]=grad[rr*width+cc];
		}
	}
	float sum=0;
	float result=0;
	for(int j=0;j<4;j++)
	{
		sum=0;
		for(int i=0;i<4;i++)
		{
			sum+=A[i]*B[i][j];
		}
		result+=sum*C[j];
	}
	Grad=result;
	
	
	
}
float Image::Sx(float x)
{
#if 1
	if (x<1e-6)
		return 1;
	else if (x>=2-1e-6)
		return 0;
//	else
	return sin(x*PI)/(x*PI);
	//if(x)
#endif
	
	if(fabs(x)<1)
		return 1-2*x*x+x*x*x;//fabs(x);
	else if(fabs(x)<2)
		return 4-8*x+5*x*x-x*x*x;//fabs(x);
	else
		return 0;

}
