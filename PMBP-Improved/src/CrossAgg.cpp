
void CrossAgg( float **RGB,float*cost,int Height,int Width,int radius,float thresh)
{
	float*temp=new float[Height*Width];
	for(int i=0;i<Height*Width;i++)
	{
		if(RGB[i][0]<0)
			continue;
		temp[i]=CrossAgg(RGB,cost,Height,Width,radius,thresh,i);
		
	}
	for(int i=0;i<Height*Width;i++)
	{
		cost[i]=temp[i];
	}
	delete[]temp;	
}
float CrossAgg( float **RGB,float*cost,int Height,int Width,int radius,float thresh,int i)
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
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
			break;
		for(int cx=x;cx<=end_x;cx++)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
			
				
		}
		for(int cx=x-1;cx>=start_x;cx--)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	for (int ry=y-1;ry>=start_y;ry--)
	{
		int location = ry*Width+x;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
			break;
		for(int cx=x;cx<=end_x;cx++)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
		for(int cx=x-1;cx>=start_x;cx--)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	for (int cx=x;cx<=end_x;cx++ )
	{
		int location = y*Width+cx;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
			break;
			
		for(int ry=y;ry<=end_y;ry++)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
		for(int ry=y-1;ry>=start_y;ry--)
		{
			
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	for (int cx=x-1;cx>=start_x;cx--)
	{
		int location = y*Width+cx;
		if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
			break;
		for(int ry=y;ry<=end_y;ry++)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
		for(int ry=y-1;ry>=start_y;ry--)
		{
			location = ry*Width+cx;
			if(fabs(RGB[location][0]-RGB[i][0])+fabs(RGB[location][1]-RGB[i][1])+fabs(RGB[location][2]-RGB[i][2])>thresh||RGB[location][0]<0)
				break;
			int sublocation=(ry-y+radius)*(radius*2+1)+(cx-x+radius);
			rem[sublocation]=location;
				
		}
	}
	
	float agg=0;
	int count=0;
	for(int k=0;k<(radius*2+1)*(radius*2+1);k++)
	{
		if(rem[k]>=0)
		{
			agg+=cost[rem[k]];
			count++;
		}
	}
	delete[]rem;
	return agg/count;
}
