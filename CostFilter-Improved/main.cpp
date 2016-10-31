#include"CostFilter.h"
#if _IMPROVED
int main(int argc,char*argv[])
{
	char guidance[200];
	char data1[200];
	char data2[200];
	char dstname[200];
	float MaxMotion=0;
	float step=1;
	CostFilter Match;
	Match.step=1;
	float eps=0.05;
	int radius=9;
	int stereo;
	if(argc>=5)
	{
		sprintf(guidance,"%s",argv[2]);
		sprintf(data1,"%s",argv[3]);
		sprintf(data2,"%s",argv[4]);
		MaxMotion=atof(argv[5]);
		
		if(strcmp(argv[1],"stereo")==0)
		{
			stereo=1;

		}
		else if(strcmp(argv[1],"flow")==0)
		{
			stereo=0;

		}
		if (argc>=7)
		{
				radius=atoi(argv[6]);	
		}
		if(argc>=8)
		       eps=atof(argv[7]);	
	}

	Match.Initial(guidance,guidance,stereo,MaxMotion,radius,eps);
	Match.LoadFeature(data1,data2);
	Match.Matching();
	return 0;
}
#else
int main(int argc,char*argv[])
{
	char leftimg[200];
	char rightimg[200];
	char dstname[200];
	float MaxMotion=0;
	int stereo;
	
	CostFilter Match;
	Match.step=1;
	float eps=0.05;
	int radius=9;
	if(argc>=4)
	{
		sprintf(leftimg,"%s",argv[2]);
		sprintf(rightimg,"%s",argv[3]);
		MaxMotion=atof(argv[4]);
		
		if(strcmp(argv[1],"stereo")==0)
		{
			stereo=1;

		}
		else if(strcmp(argv[1],"flow")==0)
		{
			stereo=0;

		}
		if (argc>=6)
		{
			radius=atoi(argv[5]);	
		}
		if(argc>=7)
		        eps=atof(argv[6]);
	}

	Match.Initial(leftimg,rightimg,stereo,MaxMotion,radius,eps);
	//imwrite("test.png",Match.img1.img);
	Match.Matching();
	return 0;
}
#endif
