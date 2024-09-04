#include"../header.h"
#include"declaration.h"
int init()
{
#ifdef DEBUG
	printf("%s Begins\n",__func__);
#endif
	//fptr[0]=shutdownServer;
	fptr[1]=vendorsHandler;
	fptr[2]=vendor1;
	fptr[3]=vendor2;
	fptr[4]=vendor3;
	fptr[5]=vendor4;
#ifdef DEBUG
	printf("%s Ends\n",__func__);  
#endif
      return 0; 
}

