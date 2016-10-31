
#include"Feature.h"
Mat cumsum( const Mat& src, const int d )
{
	int H = src.rows;
	int W = src.cols;
	Mat dest = Mat::zeros( H, W, src.type() );

	if( d == 1 ) {
		// summation over column
		for( int y = 0; y < H; y ++ ) {
			double* curData = ( double* ) dest.ptr<double>( y );
			double* preData = ( double* ) dest.ptr<double>( y );
			if( y ) {
				// not first row
				preData = ( double* ) dest.ptr<double>( y - 1 ); 
			}
			double* srcData = ( double* ) src.ptr<double>( y );
			for( int x = 0; x < W; x ++ ) {
				curData[ x ] = preData[ x ] + srcData[ x ];
			}
		}
	} else {
		// summation over row
		for( int y = 0; y < H; y ++ ) {
			double* curData = ( double* ) dest.ptr<double>( y );
			double* srcData = ( double* ) src.ptr<double>( y );
			for( int x = 0; x < W; x ++ ) {
				if( x ) {
					curData[ x ] = curData[ x - 1 ] + srcData[ x ];
				} else {
					curData[ x ] = srcData[ x ];
				}
			}
		}
	}
	return dest;
}

Mat boxfilter( const Mat& imSrc, const int r )
{
	int H = imSrc.rows;
	int W = imSrc.cols;
	// image size must large than filter size
	CV_Assert( W >= r && H >= r );
	Mat imDst = Mat::zeros( H, W, imSrc.type() );
	// cumulative sum over Y axis
	Mat imCum = cumsum( imSrc, 1 );
	// difference along Y ( [ 0, r ], [r + 1, H - r - 1], [ H - r, H ] )
	for( int y = 0; y < r + 1; y ++ ) {
		double* dstData = ( double* ) imDst.ptr<double>( y );
		double* plusData = ( double* ) imCum.ptr<double>( y + r );
		for( int x = 0; x < W; x ++ ) {
			dstData[ x ] = plusData[ x ];
		}

	}
	for( int y = r + 1; y < H - r; y ++ ) {
		double* dstData = ( double* ) imDst.ptr<double>( y );
		double* minusData = ( double*  ) imCum.ptr<double>( y - r - 1);
		double* plusData = ( double* ) imCum.ptr<double>( y + r );
		for( int x = 0; x < W; x ++ ) {
			dstData[ x ] = plusData[ x ] - minusData[ x ];
		}
	}
	for( int y = H - r; y < H; y ++ ) {
		double* dstData = ( double* ) imDst.ptr<double>( y );
		double* minusData = ( double*  ) imCum.ptr<double>( y - r - 1);
		double* plusData = ( double* ) imCum.ptr<double>( H - 1 );
		for( int x = 0; x < W; x ++ ) {
			dstData[ x ] = plusData[ x ] - minusData[ x ];
		}
	}

	// cumulative sum over X axis
	imCum = cumsum( imDst, 2 );
	for( int y = 0; y < H; y ++ ) {
		double* dstData = ( double* ) imDst.ptr<double>( y );
		double* cumData = ( double* ) imCum.ptr<double>( y );
		for( int x = 0; x < r + 1; x ++ ) {
			dstData[ x ] = cumData[ x + r ];
		}
		for( int x = r + 1; x < W - r; x ++ ) {
			dstData[ x ] = cumData[ x + r ] - cumData[ x - r - 1 ];
		}
		for( int x = W - r; x < W; x ++ ) {
			dstData[ x ] = cumData[ W - 1 ] - cumData[ x - r - 1 ];
		}
	}
	return imDst;
}

void Feature::Extractor(vector<Mat> &DataIn,vector<Mat>&DataOut,int i,int j)
{
	Mat temp;
	Mat out=Mat::zeros(height,width,CV_32FC1);
	for(int k=0;k<Layers[i].Nin;k++)
	{
		Mat Kernel(Layers[i].Ksize,Layers[i].Ksize,CV_32FC1);
		for(int row=0;row<Layers[i].Ksize;row++)
		{
			for(int col=0;col<Layers[i].Ksize;col++)
				Kernel.at<float>(row,col)=Layers[i].weights[j][k][row*Layers[i].Ksize+col];
		}
		filter2D(DataIn[k], temp,-1, Kernel);//, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT )
		out=out+temp;
		
		
	}
	out=out+Layers[i].biases[j];
	if(i<Nlayer-1)
		DataOut[j]=cv::max(out, (double)0);
	else
	{
		cv::exp(out*-1,out);
		cv::divide(1, out+1, out);
		
		out.copyTo(DataOut[j]);
	}
	
	
	
}
void Feature::Extractor()
{
	if(Layers==NULL)
	{
		cout<<"No model for feature extracting..."<<endl;
		exit(0);
	}
	vector<Mat>DataIn;
	
	vector<Mat>DataOut;
	
	for(int k=Layers[0].Nin-1;k>=0;k--){
	Mat tem(height,width,CV_32FC1);
	omp_set_num_threads(NUM_THREADS);
	float mean=0;
	float std=0;
if(Layers[0].Nin==3)
{
#if 1
#pragma omp parallel for
	for(int i=0;i<height*width;i++)
		mean+=(float)(img.at<Vec3b>(i/width,i%width)[k])/255.0;
	mean=mean/height/width;
	for(int i=0;i<height*width;i++)
		std+=pow((float)(img.at<Vec3b>(i/width,i%width)[k])/255.0-mean,2.0);
		std=sqrt(std/(height*width-1));
	for(int i=0;i<height*width;i++)
	{
		
		tem.at<float>(i/width,i%width)=((float)(img.at<Vec3b>(i/width,i%width)[k])/255.0-mean)/std;
	}
#else
#pragma omp parallel for
	for(int i=0;i<height*width;i++)
	{
		
		tem.at<float>(i/width,i%width)=(float)(img.at<Vec3b>(i/width,i%width)[k])/255.0;
	}
#endif	

}
else if(Layers[0].Nin==1)
{
	Mat gray;
	cvtColor(img,gray, CV_BGR2GRAY);  
#if 1
#pragma omp parallel for
	for(int i=0;i<height*width;i++)
		mean+=(float)(gray.at<uchar>(i/width,i%width))/255.0;
	mean=mean/height/width;
	for(int i=0;i<height*width;i++)
		std+=pow((float)(gray.at<uchar>(i/width,i%width))/255.0-mean,2.0);
	std=sqrt(std/(height*width-1));
	for(int i=0;i<height*width;i++)
	{
		
		tem.at<float>(i/width,i%width)=((float)(gray.at<uchar>(i/width,i%width))/255.0-mean)/std;
	}
#else
	#pragma omp parallel for
	for(int i=0;i<height*width;i++)
	{
		
		tem.at<float>(i/width,i%width)=(float)(gray.at<uchar>(i/width,i%width))/255.0;
	}
#endif
}
	DataOut.push_back(tem);
		
	}


	
	
	for(int i=0;i<Nlayer;i++)
	{
		DataIn.clear();
		for(int j=0;j<Layers[i].Nin;j++)
			DataIn.push_back(DataOut[j]);
		DataOut.clear();
		for(int j=0;j<Layers[i].Nout;j++)
		{
			Mat temp(height,width,CV_32FC1);
			DataOut.push_back(temp);
		}
	//	cout<<DataIn.size()<<'	'<<DataOut.size()<<endl;
		omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
		for(int j=0;j<Layers[i].Nout;j++)
		{
			Extractor(DataIn,DataOut,i,j);
		}
	}
	if(data==NULL)
	{
		data=new float*[width*height];
		for(int i=0;i<width*height;i++)
			data[i]=new float[channel*2+1];
	
		for(int j=0;j<Layers[Nlayer-1].Nout;j++)
		{
		omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
			for(int i=0;i<height*width;i++)
			{
		
				data[i][j+1]=DataOut[j].at<float>(i/width,i%width);
			}
		
		}
	}
	else
	{
		for(int j=0;j<Layers[Nlayer-1].Nout;j++)
		{
		omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
			for(int i=0;i<height*width;i++)
			{
		
				data[i][j+channel+1]=DataOut[j].at<float>(i/width,i%width);
			}
		
		}
	}

	DataIn.clear();
	vector<Mat>().swap(DataIn);
	DataOut.clear();
	vector<Mat>().swap(DataOut);

}
void Feature::LoadModel(char*filename)
{
	FILE*fp;
	fp=fopen(filename,"rb");
	if(!fp)
	{
		std::cout<<"Cannot open the file "<<filename<<endl;
		exit(0);
	}
	float temp;
	fread(&temp,sizeof(float),1,fp);
	Nlayer1=(int)temp;
	
	Layers1=new Layer[Nlayer1];
	
	for (int i=0;i<Nlayer1;i++)
	{
		fread(&temp,sizeof(float),1,fp);Layers1[i].Ksize=(int)temp;
		fread(&temp,sizeof(float),1,fp);Layers1[i].Nin=(int)temp;
		fread(&temp,sizeof(float),1,fp);Layers1[i].Nout=(int)temp;
		
		Layers1[i].weights=new float**[Layers1[i].Nout];
		Layers1[i].biases=new float[Layers1[i].Nout];
		for(int j=0;j<Layers1[i].Nout;j++)
		{
			Layers1[i].weights[j]=new float*[Layers1[i].Nin];
			for(int k=0;k<Layers1[i].Nin;k++)
			{
				Layers1[i].weights[j][k]=new float[Layers1[i].Ksize*Layers1[i].Ksize];
				fread(Layers1[i].weights[j][k],sizeof(float),Layers1[i].Ksize*Layers1[i].Ksize,fp);
			}
		}
		fread(Layers1[i].biases,sizeof(float),Layers1[i].Nout,fp);		
	}

///load smooth model;

	fread(&temp,sizeof(float),1,fp);
	Nlayer2=(int)temp;

	Layers2=new Layer[Nlayer2];
	
	for (int i=0;i<Nlayer2;i++)
	{
		fread(&temp,sizeof(float),1,fp);Layers2[i].Ksize=(int)temp;
		fread(&temp,sizeof(float),1,fp);Layers2[i].Nin=(int)temp;
		fread(&temp,sizeof(float),1,fp);Layers2[i].Nout=(int)temp;
		
		Layers2[i].weights=new float**[Layers2[i].Nout];
		Layers2[i].biases=new float[Layers2[i].Nout];
		for(int j=0;j<Layers2[i].Nout;j++)
		{
			Layers2[i].weights[j]=new float*[Layers2[i].Nin];
			for(int k=0;k<Layers2[i].Nin;k++)
			{
				Layers2[i].weights[j][k]=new float[Layers2[i].Ksize*Layers2[i].Ksize];
				fread(Layers2[i].weights[j][k],sizeof(float),Layers2[i].Ksize*Layers2[i].Ksize,fp);
			}
		}
		fread(Layers2[i].biases,sizeof(float),Layers2[i].Nout,fp);		
	}

	fclose(fp);

}
void Feature::SaveFeature(char*filename)
{
	FILE*fp;
	fp=fopen(filename,"wb");        
 	if(fp==0)
	{
		cout<<"Cannot open file "<<filename<<"..."<<endl;
		exit(0);
	}
	fwrite(&height,sizeof(int),1,fp);
	fwrite(&width,sizeof(int),1,fp);
	fwrite(&channel,sizeof(int),1,fp);
	if(data==NULL)
	{
		cout<<"No available features can be saved!"<<endl;
		exit(0);
	}
	for(int i=0;i<width*height;i++)
	{
  		fwrite(data[i],sizeof(float),2*channel+1,fp);
	}
  	//fwrite(&a,sizeof(int),1,stdout);
  	fclose(fp);
}
void Feature::FreeMem()
{
	if(tag!=NULL)
		delete[]tag;
	if(data!=NULL)
	{
		for(int i=0;i<width*height;i++)
			delete[]data[i];
		delete[]data;
		data=NULL;
	}
	if(Layers1!=NULL)
	{
		for(int i=0;i<Nlayer1;i++)
		{
			for(int j=0;j<Layers1[i].Nout;j++)
			{
				for(int k=0;k<Layers1[i].Nin;k++)
				{
					delete []Layers1[i].weights[j][k];	
				}
				delete[] Layers1[i].weights[j];
			}
			delete[]Layers1[i].weights;
		}
		delete[]Layers1;
		Layers1=NULL;
	}
	if(Layers2!=NULL)
	{
		for(int i=0;i<Nlayer2;i++)
		{
			for(int j=0;j<Layers2[i].Nout;j++)
			{
				for(int k=0;k<Layers2[i].Nin;k++)
				{
					delete []Layers2[i].weights[j][k];	
				}
				delete[] Layers2[i].weights[j];
			}
			delete[]Layers2[i].weights;
		}
		delete[]Layers2;
		Layers2=NULL;
	}
	Layers=NULL;
}

void Feature::TagAllPixels(char*filename)
{

	int lowThreshold=10;
	int maxThreshold = 100;

	int kernel_size = 3;
	Mat edges;
	Mat gray=imread(filename,0);
	
  	blur( gray, edges, Size(3,3) );

  /// Canny detector
  	Canny( edges, edges, lowThreshold, maxThreshold, kernel_size );
	Mat edg(height,width,CV_64FC1);
	for(int row=0;row<height;row++)
	for(int col=0;col<width;col++)
		edg.at<double>(row,col)=(double)edges.at<uchar>(row,col);
	
	Mat temp=boxfilter(edg,5);

	for(int row=0;row<height;row++){
	for(int col=0;col<width;col++)
	{
		if((int)temp.at<double>(row,col)>=0.5)
			data[row*width+col][0]=1;
		else
			data[row*width+col][0]=-1;
	}
	}
	//cout<<width<<'	'<<height<<'	'<<channel<<endl;

 
	
}
void Feature::Initial(int Height,int Width,int Channel)
{
	width=Width;
	height=Height;
	channel=Channel;
	
	
}
void Feature::GetFeature(char*imgname,char*modelname,char*featurename)
{
	Initial(imgname,modelname);
	SaveFeature(featurename);
	FreeMem();
}
void Feature::Initial(char*imgname,char*modelname)
{
	LoadModel(modelname);
	img=imread(imgname,1);
	width=img.size().width;
	height=img.size().height;
	channel=Layers1[Nlayer1-1].Nout;
	//cout<<height<<'	'<<width<<'	'<<Layers2[Nlayer2-1].Nout<<'	'<<endl;	
	Nlayer=Nlayer1;
	Layers=Layers1;
	Extractor();
	Nlayer=Nlayer2;
	Layers=Layers2;
	Extractor();
	TagAllPixels(imgname);
	
//	cout<<channel<<endl;
	
}
void Feature::LoadFeature(char* filename)
{
	
	FILE*fp;
	fp=fopen(filename,"rb");
	if(!fp)
	{
		std::cout<<"Cannot open the file "<<filename<<endl;
		exit(0);
	}
	fread(&height,sizeof(float),1,fp);
	fread(&width,sizeof(float),1,fp);
	fread(&channel,sizeof(float),1,fp);
	if(data==NULL)
	{
		data=new float*[width*height];
		for(int i=0;i<width*height;i++)
			data[i]=new float[channel*2+1];
	}
	
	for(int row=0;row<height;row++)
	{
		for(int col=0;col<width;col++)
		{
			int location=row*width+col;
			
			fread(data[location],sizeof(float),channel*2+1,fp);
			//fread(pLine,sizeof(float),nCols,fp);
		}
	}
//	channel=channel/2;
	fclose(fp);

}
void Feature::LinearData(int x,int y,float*rem,int tag)
{
	if (x<0||y<0||x>width-1||y>height-1)
	{
		cout<<"Out of range..."<<endl;
		std::cout<<"error! LinearData!!"<<std::endl;	
		exit(0);
	}
	int base=1;
	if(tag>0)
		base=1;
	else
		base=channel+1;
	int location=y*width+x;
	
	for(int k=0;k<channel;k++)
	{
		rem[k]=data[location][k+base];
	}
	
}
void Feature::LinearData(float x,int y,float*rem,int tag)
{
	if (x<0||y<0||x>width-1||y>height-1)
	{
		cout<<"Out of range..."<<endl;
		std::cout<<"error! LinearData!!"<<std::endl;	
		exit(0);
	}
	int base=1;
	if(tag>0)
		base=1;
	else
		base=channel+1;
	float weight[2];
	int location[2];
	
	int x1=(int )x;
	int x2=min(width-1,(int)x+1);
	weight[0]=(x2-x);weight[1]=(x-x1);
	location[0]=y*width+x1;location[1]=y*width+x2;
	for(int k=0;k<channel;k++)
	{
		rem[k]=data[location[0]][k+base]*weight[0]+data[location[1]][k+base]*weight[1];
	}
	
}
void Feature::LinearData(float x,float y,float*rem,int tag)
{
	if (x<0||y<0||x>width-1||y>height-1)
	{
		cout<<"Out of range..."<<endl;
		std::cout<<"error! LinearData!!"<<std::endl;	
		exit(0);
	}
	int base=1;
	if(tag>0)
		base=1;
	else
		base=channel+1;
	float weight[4];
	int location[4];
	int y1=(int )y;
	int y2=min((int)y+1,height-1);
	int x1=(int )x;
	int x2=min(width-1,(int)x+1);
	weight[0]=(x2-x)*(y2-y);weight[1]=(x-x1)*(y2-y);
	weight[2]=(x2-x)*(y-y1);weight[3]=(x-x1)*(y-y1);
	location[0]=y1*width+x1;location[1]=y1*width+x2;
	location[2]=y2*width+x1;location[3]=y2*width+x2;
	for(int k=0;k<channel;k++)
	{
		rem[k]=data[location[0]][k+base]*weight[0]+data[location[1]][k+base]*weight[1]+data[location[2]][k+base]*weight[2]+data[location[3]][k+base]*weight[3];
	}
	
}
