#include"Feature.h"
#if 1
int main(int argc,char*argv[])
{
	Feature ext;
	char imgname[100];
	char modelname[100];
	char featurename[100];
	if(argc==4)
	{
		sprintf(imgname,"%s",argv[1]);
		sprintf(modelname,"%s",argv[2]);
		sprintf(featurename,"%s",argv[3]);
		ext.GetFeature(imgname,modelname,featurename);
	}
	else if(argc==5)
	{
		sprintf(imgname,"%s",argv[1]);
		sprintf(modelname,"%s",argv[2]);
		sprintf(featurename,"%s",argv[3]);
		ext.NUM_THREADS=atoi(argv[4]);
		ext.GetFeature(imgname,modelname,featurename);
	}
	else
	{
		cout<<"Please use the command like this:"<<endl;
		cout<<"./Extractor [image name] [feature model] [output name]"<<endl;
		cout<<"./Extractor [image name] [feature model] [output name] [thread number]"<<endl;
	}
	return 0;
}

#endif

