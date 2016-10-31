#include "image_operator.h"
#include "image.h"
#include "graph_particles.h"

//------------------------------------------------------------------------------

namespace pmbp {
  
//------------------------------------------------------------------------------
  
ImageOperator::ImageOperator(float***Data,int Channel,Image** img, Image** grad, Image** filt, int* ww, int* hh, Parameters& params, DisplacementFunction f) :
  data(Data),images(img), gradients(grad), filtered(filt), w(ww), h(hh), parameters(params), displacement_function(f){
	channel=Channel;

}
  
//------------------------------------------------------------------------------
  
ImageOperator::~ImageOperator(){
  
}

//------------------------------------------------------------------------------
#if 1
void ImageOperator::CrossRegion(View view,int x,int y,float *error, float thresh)const
{
	View target = view;
 	// View source = OtherView(target);
	float xc_target = x;
  float yc_target = y;
  
  // Patch boundaries
  float start_x = std::max(xc_target - parameters.patch_size, 0.f);
  float start_y = std::max(yc_target - parameters.patch_size, 0.f);
  float end_x = std::min((float)(xc_target + parameters.patch_size), (float)(w[target]-1));
  float end_y = std::min((float)(yc_target + parameters.patch_size), (float)(h[target]-1));
  
  // Center color for AWS
	int center_colour = filtered[view]->GetGridPixel(x, y);
	float r_center = Image::Red(center_colour);
	float g_center = Image::Green(center_colour);
	float b_center = Image::Blue(center_colour);
	
	for(int i=0;i<(int)((end_x-start_x+1)*(end_y-start_y+1));i++)
		error[i]=0;
	
	int PatchWidth=end_x-start_x+1;
	for (int ry=y;ry<=end_y;ry++)
	{
		int location = filtered[view]->GetGridPixel(x, ry);
		float r_ = Image::Red(location);
		float g_ = Image::Green(location);
		float b_ = Image::Blue(location);
		if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
			break;
		for(int cx=x;cx<=end_x;cx++)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
		for(int cx=x-1;cx>=start_x;cx--)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
	}
	for (int ry=y-1;ry>=start_y;ry--)
	{
		int location = filtered[view]->GetGridPixel(x, ry);
		float r_ = Image::Red(location);
		float g_ = Image::Green(location);
		float b_ = Image::Blue(location);
		if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
			break;
		for(int cx=x;cx<=end_x;cx++)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
		for(int cx=x-1;cx>=start_x;cx--)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
	}
	for (int cx=x;cx<=end_x;cx++ )
	{
		int location = filtered[view]->GetGridPixel(cx, y);
		float r_ = Image::Red(location);
		float g_ = Image::Green(location);
		float b_ = Image::Blue(location);
		if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
			break;
		for(int ry=y;ry<=end_y;ry++)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
		for(int ry=y-1;ry>=start_y;ry--)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
	}
	for (int cx=x-1;cx>=start_x;cx--)
	{
		int location = filtered[view]->GetGridPixel(cx, y);
		float r_ = Image::Red(location);
		float g_ = Image::Green(location);
		float b_ = Image::Blue(location);
		if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
			break;
		for(int ry=y;ry<=end_y;ry++)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
		for(int ry=y-1;ry>=start_y;ry--)
		{
			
			location = filtered[view]->GetGridPixel(cx, ry);
			r_ = Image::Red(location);
			g_ = Image::Green(location);
			b_ = Image::Blue(location);
			if(fabs(r_-r_center)+fabs(g_-g_center)+fabs(b_-b_center)>thresh)
				break;
			location=(ry-start_y)*PatchWidth+cx-start_x;
			error[location]=-1;
				
		}
	}
}
 float ImageOperator::PatchCost(View view, int x, int y, const State& state, float threshold)const
{
  //float error(0);
  //return CrossAgg(view, x, y,state,threshold);
  View target = view;
  View source = OtherView(target);
  
  // Center pixel
  float xc_target = x;
  float yc_target = y;
  
  // Patch boundaries
  float start_x = std::max(xc_target - parameters.patch_size, 0.f);
  float start_y = std::max(yc_target - parameters.patch_size, 0.f);
  float end_x = std::min((float)(xc_target + parameters.patch_size), (float)(w[target]-1));
  float end_y = std::min((float)(yc_target + parameters.patch_size), (float)(h[target]-1));
  
  // Center color for AWS
	int center_colour = filtered[view]->GetGridPixel(x, y);
	float r_center = Image::Red(center_colour);
	float g_center = Image::Green(center_colour);
	float b_center = Image::Blue(center_colour);
	float *error=new float[(int)((end_x-start_x+1)*(end_y-start_y+1))];
	
	CrossRegion(view,x,y,error,  parameters.alpha*100);
	int PatchWidth=end_x-start_x+1;
	
omp_set_num_threads(8);
#pragma omp parallel for
	for(int i=0;i<(int)((end_x-start_x+1)*(end_y-start_y+1));i++)
	{
		//std::cout<<i<<' ';
		if(error[i]>=-0.5)
			continue;
		int y_target=i/PatchWidth+start_y;
		int x_target=i%PatchWidth+start_x;
		 float d_x, d_y;
      		displacement_function(x_target, y_target, state, d_x, d_y);
      
      // Get source coordinate
     		 float x_source = x_target + d_x;
     		 float y_source = y_target + d_y;
		error[i]= PixelCost(target, source, x_source, y_source, x_target, y_target, r_center, g_center, b_center);
		
	}
	
	float ee=0;
	for(int i=0;i<(end_x-start_x)*(end_y-start_y);i++)
	{
		ee+=error[i];
  		
	}
	
	delete[]error;
	//if(ee > threshold)
      	//	return parameters.infinity;
	return ee;
  
}
#else
 float ImageOperator::PatchCost(View view, int x, int y, const State& state, float threshold)const
{
  //float error(0);
  
  View target = view;
  View source = OtherView(target);
  
  // Center pixel
  float xc_target = x;
  float yc_target = y;
  
  // Patch boundaries
  float start_x = std::max(xc_target - parameters.patch_size, 0.f);
  float start_y = std::max(yc_target - parameters.patch_size, 0.f);
  float end_x = std::min((float)(xc_target + parameters.patch_size), (float)(w[target]-1));
  float end_y = std::min((float)(yc_target + parameters.patch_size), (float)(h[target]-1));
  
  // Center color for AWS
	int center_colour = filtered[view]->GetGridPixel(x, y);
	float r_center = Image::Red(center_colour);
	float g_center = Image::Green(center_colour);
	float b_center = Image::Blue(center_colour);
	float *error=new float[(int)((end_x-start_x)*(end_y-start_y))];
	int PatchWidth=end_x-start_x;
omp_set_num_threads(6);
#pragma omp parallel for
	for(int i=0;i<(int)((end_x-start_x)*(end_y-start_y));i++)
	{
		//std::cout<<i<<' ';
		int y_target=i/PatchWidth+start_y;
		int x_target=i%PatchWidth+start_x;
		 float d_x, d_y;
      		displacement_function(x_target, y_target, state, d_x, d_y);
      
      // Get source coordinate
     		 float x_source = x_target + d_x;
     		 float y_source = y_target + d_y;
		error[i]= PixelCost(target, source, x_source, y_source, x_target, y_target, r_center, g_center, b_center);
		
	}
	
	float ee=0;
	for(int i=0;i<(end_x-start_x)*(end_y-start_y);i++)
	{
		ee+=error[i];
  		
	}
	
	delete[]error;
	//if(ee > threshold)
      	//	return parameters.infinity;
	return ee;
  
}
float ImageOperator::PatchCost(View view, int x, int y, const State& state, float threshold) const
{
  float error(0);
  
  View target = view;
  View source = OtherView(target);
  
  // Center pixel
  float xc_target = x;
  float yc_target = y;
  
  // Patch boundaries
  float start_x = std::max(xc_target - parameters.patch_size, 0.f);
  float start_y = std::max(yc_target - parameters.patch_size, 0.f);
  float end_x = std::min((float)(xc_target + parameters.patch_size), (float)(w[target]-1));
  float end_y = std::min((float)(yc_target + parameters.patch_size), (float)(h[target]-1));
  
  // Center color for AWS
	int center_colour = filtered[view]->GetGridPixel(x, y);
	float r_center = Image::Red(center_colour);
	float g_center = Image::Green(center_colour);
	float b_center = Image::Blue(center_colour);
  
  for(int y_target = start_y; y_target <= end_y; ++y_target){
    for(int x_target = start_x; x_target <= end_x; ++x_target){
      
      float d_x, d_y;
      displacement_function(x_target, y_target, state, d_x, d_y);
      
      // Get source coordinate
      float x_source = x_target + d_x;
      float y_source = y_target + d_y;
      
      error += PixelCost(target, source, x_source, y_source, x_target, y_target, r_center, g_center, b_center);
    }
    
    // Early termination, must pass unary minus message sum as the message sum
    // will be added to the unary
    if(error > threshold){
      return parameters.infinity;
    }
    
  }
  
  return error;
}
#endif


void ImageOperator::LinearData(View target, float x,float y,float*rem,int tag)const
{
	//int channel=64;
	int width=w[target];
	int height=h[target];
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
	for(int k=0;k<channel;k++)
	{
		rem[k]=data[target][location[0]][k+base]*weight[0]+data[target][location[1]][k+base]*weight[1]+data[target][location[2]][k+base]*weight[2]+data[target][location[3]][k+base]*weight[3];
	}
	
	
}
void ImageOperator::CrossAgg( float **RGB,int*&temp,int Height,int Width,int radius,float thresh,int i)const
{
	int y=i/Width;
	int x=i%Width;
	int end_y=y+radius<Height-1?y+radius:Height-1;
	int end_x=x+radius<Width-1?x+radius:Width-1;
	int start_x=x-radius>0?x-radius:0;
	int start_y=y-radius>0?y-radius:0;
	int *rem=new int[(radius*2+1)*(radius*2+1)];
	for(int k=0;k<(radius*2+1)*(radius*2+1);k++)
		rem[k]=-1;
	
	for (int ry=y;ry<=end_y;ry++)
	{
		int location = ry*Width+x;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
			break;
		for(int cx=x;cx<=end_x;cx++)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
			
				
		}
		for(int cx=x-1;cx>=start_x;cx--)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	for (int ry=y-1;ry>=start_y;ry--)
	{
		int location = ry*Width+x;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
			break;
		for(int cx=x;cx<=end_x;cx++)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
		for(int cx=x-1;cx>=start_x;cx--)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	for (int cx=x;cx<=end_x;cx++ )
	{
		int location = y*Width+cx;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
			break;
			
		for(int ry=y;ry<=end_y;ry++)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
		for(int ry=y-1;ry>=start_y;ry--)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	for (int cx=x-1;cx>=start_x;cx--)
	{
		int location = y*Width+cx;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
			break;
		for(int ry=y;ry<=end_y;ry++)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
		for(int ry=y-1;ry>=start_y;ry--)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	
	
	int count=0;
	for(int k=0;k<(radius*2+1)*(radius*2+1);k++)
	{
		if(rem[k]>=0)
		{
			//agg+=cost[rem[k]];
			temp[count]=rem[k];
			count++;
		}
	}
	delete[]rem;
	//return agg/count;
}
void ImageOperator::CrossAgg( float **RGB,float*&cost,int Height,int Width,int radius,float thresh)const
{
	float*temp=new float[Height*Width];
	int**rem=new int*[Height*Width];
	int total=(radius*2+1)*(radius*2+1);
//#pragma omp parallel for
	for(int i=0;i<Height*Width;i++)
	{
		rem[i]=new int[total];
		for(int j=0;j<total;j++)
		{
			rem[i][j]=-1;
		}
	}
#pragma omp parallel for
	for(int i=0;i<Height*Width;i++)
	{
		//if(RGB[i][0]<0)
		//	continue;
		CrossAgg(RGB,rem[i],Height,Width,radius,thresh,i);
		
	}
	int Max_Iter=std::max(std::max(Height,Width)/2/radius,3);
    for(int iter=0;iter<Max_Iter;iter++)
    {
#pragma omp parallel for
	for(int i=0;i<Height*Width;i++)
	{
		temp[i]=0;
		float count=1e-6;
		//if(RGB[i][0]<0)
		//	continue;
		for(int j=0;j<total;j++)
		{
			if(rem[i][j]<0)
				break;
			temp[i]+=cost[rem[i][j]];
			count=count+1;
		}
		temp[i]=temp[i]/count;
	//	if(temp[i]!=temp[i])
	//		printf("error for CrossAggregation...\n");
	}
#pragma omp parallel for
	for(int i=0;i<Height*Width;i++)
	{
		cost[i]=temp[i];
	}
    }

//#pragma omp parallel for
	for(int i=0;i<Height*Width;i++)
	{
		//if(cost[i]!=cost[i])
		//	printf("")
		delete[]rem[i];
	}
	delete[]temp;
	delete[]rem;
}
float ImageOperator::CrossAgg(View view, int x, int y, const State& state, float threshold) const
{
 	 float error(0);
  	//printf("test\n");
  	View target = view;
  	View source = OtherView(target);
  
  // Center pixel
  	float xc_target = x;
  	float yc_target = y;
  
  // Patch boundaries
  	float start_x = std::max(xc_target - parameters.patch_size, 0.f);
  	float start_y = std::max(yc_target - parameters.patch_size, 0.f);
  	float end_x = std::min((float)(xc_target + parameters.patch_size), (float)(w[target]-1));
 	float end_y = std::min((float)(yc_target + parameters.patch_size), (float)(h[target]-1));
	int total=(int)((end_y-start_y+1)*(end_x-start_x+1));
	int PatchWidth=(int)(end_x-start_x+1);
  	float**RGB=new float*[total];
	for(int i=0;i<total;i++)
	{
	
		RGB[i]=new float[3];
	}
	float *cost=new float[total];
  
#pragma omp parallel for
  	for(int i=0;i<total;i++)
	{
  	
		int y_target=i/PatchWidth+start_y;
		int x_target=i%PatchWidth+start_x;
		int target_colour = filtered[view]->GetGridPixel(x_target, y_target);
		int location=i;
		RGB[location][0] = Image::Red(target_colour);
		RGB[location][1] = Image::Green(target_colour);
		RGB[location][2] = Image::Blue(target_colour);
      		
      		float d_x, d_y;
      		displacement_function(x_target, y_target, state, d_x, d_y);
     		float x_source = x_target + d_x;
      		float y_source = y_target + d_y;
      
     		 cost[location]= PixelCost(target, source, x_source, y_source, x_target, y_target);
    
 	}
	int radius=5;
	float thresh=30;
	//int Iter=parameters.patch_size/radius;
	//Iter=Iter>4?Iter:4;
	//for(int i=0;i<Iter;i++)
	CrossAgg(RGB,cost,(int)(end_y-start_y+1),(int)(end_x-start_x+1),radius,thresh);
	int location=(y-start_y)*PatchWidth+(x-start_x);
#if 0
	error=cost[location];
#else
	error=0;
	 // Center color for AWS

	for(int i=0;i<total;i++)
	{
		float diff_asw = fabs(RGB[i][0]-RGB[location][0])+fabs(RGB[i][1]-RGB[location][1])+fabs(RGB[i][2]-RGB[location][2]);
   		float w = exp(-(diff_asw)/parameters.asw);
		error+=w*cost[i];
	//	if(cost[i]!=cost[i]){
	//		printf("(%d,%d) %d %f %f\n",x,y,i,w,cost[i]);exit(0);}
	
	}
	
	
#endif
/*	
	if((int)fabs(y-(float)(h[target]-1))==2)
	{
		if(!(error>=0&&error<1000)){
			
		printf("\n(%d,%d) %.2f %d\n",x,y,error,total);
		for(int i=0;i<total;i++)
			printf("%.2f ",cost[i]);}
	
	}*/
  	delete[]cost;
	for(int i=0;i<total;i++)
	{
		delete[]RGB[i];
	}
	delete[] RGB;
	
		
  return error;
}
float ImageOperator::PixelCost(View target, View source, float x_source, float y_source, float x_target, float y_target) const
{
  float error(0.f);
  //int channel=64;
  int width=w[target];
 int height=h[target];
 float *rem=new float[channel];
  float tag=data[target][(int)(0.5+y_target)*width+(int)(x_target+0.5)][0];
  if(x_source>=0&&y_source>=0&&x_source<=width-1&&y_source<=height-1){
    
    // Get target colour
   
   LinearData(source,x_source,y_source,rem,tag);
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
	norm1+=pow((float)data[target][(int)(y_target+0.5)*width+(int)(x_target+0.5)][k+base],2.0);
		norm2+=pow((float)rem[k],2.0);
	}
	norm1=sqrt(norm1);
	norm2=sqrt(norm2);
   for(int k=0;k<channel;k++)
	error+=pow((float)(data[target][(int)(y_target+0.5)*width+(int)(x_target+0.5)][k+base]/norm1-rem[k]/norm2),2.0);
   delete[] rem;
 
  return error;
}
//------------------------------------------------------------------------------
 #if 1

float ImageOperator::PixelCost(View target, View source, float x_source, float y_source, float x_target, float y_target, float r_center, float g_center, float b_center) const
{
  float error(0.f);
 // int channel=64;
  int width=w[target];
 int height=h[target];
 float *rem=new float[channel];
  if(x_source>=0&&y_source>=0&&x_source<=width-1&&y_source<=height-1){
    
    // Get target colour
   
   LinearData(source,x_source,y_source,rem,data[target][(int)(0.5+y_target)*width+(int)(x_target+0.5)][0]);
	}
   else
	{
		for(int k=0;k<channel;k++)
			rem[k]=1.0/sqrt((double)channel);
	}
	float norm1=1e-6;
	float norm2=1e-6;
	int base=1;
	if (data[target][(int)(0.5+y_target)*width+(int)(x_target+0.5)][0]<0)
		base=channel+1;
	 for(int k=0;k<channel;k++)
	{
	norm1+=pow((float)data[target][(int)(y_target+0.5)*width+(int)(x_target+0.5)][k+base],2.0);
		norm2+=pow((float)rem[k],2.0);
	}
	norm1=sqrt(norm1);
	norm2=sqrt(norm2);
   for(int k=0;k<channel;k++)
	error+=pow((float)(data[target][(int)(y_target+0.5)*width+(int)(x_target+0.5)][k+base]/norm1-rem[k]/norm2),2.0);
   delete[] rem;
    // Adaptive support weight
    float filt_r, filt_g, filt_b;
    filtered[target]->GetInterpolatedPixel(x_target, y_target, filt_r, filt_g, filt_b);
    
    float diff_asw = (fabs(r_center-filt_r)+fabs(g_center-filt_g)+fabs(b_center-filt_b));
    float w = exp(-(diff_asw)/parameters.asw);
    
  
    error = std::min(error, parameters.tau2);
   // error=std::max((float)(error-0.32),(float)(0.0));
    error = w*error;
   
/*
  else{
   
   float maxmatchcosts = (1.f - parameters.alpha) * parameters.tau1 + parameters.alpha * parameters.tau2;
   float bordercosts = maxmatchcosts * parameters.border;
   
   // Adaptive support weight
   float filt_r, filt_g, filt_b;
   filtered[target]->GetInterpolatedPixel(x_target, y_target, filt_r, filt_g, filt_b);
   
   float diff_asw = (fabs(r_center-filt_r)+fabs(g_center-filt_g)+fabs(b_center-filt_b));
   float w = exp(-(diff_asw)/parameters.asw);
   
   error = w*(bordercosts);
  }
*/
  return error;
}
#else
float ImageOperator::PixelCost(View target, View source, float x_source, float y_source, float x_target, float y_target, float r_center, float g_center, float b_center) const
{
  float error(0.f);
  
  if(images[source]->IsInside(x_source, y_source)){
    
    // Get target colour
    int target_colour = images[target]->GetGridPixel(x_target, y_target);
    unsigned char r_t, g_t, b_t;
    Image::DecodeColour(target_colour, r_t, g_t, b_t);
    
    // Get target gradient colour
    int target_gradient_colour = gradients[target]->GetGridPixel(x_target, y_target);
    float dr_t = Image::Red(target_gradient_colour);
    
    // Get source colour
    float r_s, g_s, b_s;
    images[source]->GetInterpolatedPixel(x_source, y_source, r_s, g_s, b_s);
    
    // Get source gradient
    float dr_s, dg_s, db_s;
    gradients[source]->GetInterpolatedPixel(x_source, y_source, dr_s, dg_s, db_s);
    
    // Difference
    float diff_colour = (fabs(float(r_t)-float(r_s))+fabs(float(g_t)-float(g_s))+fabs(float(b_t)-float(b_s)))/3.f;
    float diff_gradient = fabs(float(dr_t)-float(dr_s));
    
    // Adaptive support weight
    float filt_r, filt_g, filt_b;
    filtered[target]->GetInterpolatedPixel(x_target, y_target, filt_r, filt_g, filt_b);
    
    float diff_asw = (fabs(r_center-filt_r)+fabs(g_center-filt_g)+fabs(b_center-filt_b));
    float w = exp(-(diff_asw)/parameters.asw);
    
    diff_colour = std::min(diff_colour, parameters.tau1);
    diff_gradient = std::min(diff_gradient, parameters.tau2);
    
    error = w*((1.f-parameters.alpha)*diff_colour + parameters.alpha*diff_gradient);
  }
  else{
   
   float maxmatchcosts = (1.f - parameters.alpha) * parameters.tau1 + parameters.alpha * parameters.tau2;
   float bordercosts = maxmatchcosts * parameters.border;
   
   // Adaptive support weight
   float filt_r, filt_g, filt_b;
   filtered[target]->GetInterpolatedPixel(x_target, y_target, filt_r, filt_g, filt_b);
   
   float diff_asw = (fabs(r_center-filt_r)+fabs(g_center-filt_g)+fabs(b_center-filt_b));
   float w = exp(-(diff_asw)/parameters.asw);
   
   error = w*(bordercosts);
  }
  
  return error;
}
 #endif 
//------------------------------------------------------------------------------
  
bool ImageOperator::IsStateValid(View view, int x, int y, const State& state) const
{
  float dx, dy;
  displacement_function(x, y, state, dx, dy);
  
  // Check that the displacement is not more than the max motion
  if(parameters.max_motion!=0.f && dx*dx+dy*dy>parameters.max_motion*parameters.max_motion)
    return false;
  
  // Check that we are still in the image
  if(!images[view]->IsInside(x+dx, y+dy))
    return false;
  
  return true;
}
  
//------------------------------------------------------------------------------
  
}

//------------------------------------------------------------------------------
