#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"

int init()
{
#ifdef DEBUG
	printf("%s Begins\n",__func__);
#endif
	fptr[0]=createInfra;
	//fptr[1]=shutdownServer;
	fptr[2]=createPipe;
	fptr[3]=createFifo;
	fptr[4]=createMsgQ;
	fptr[5]=createSharedM;
	fptr[6]=requestHandler;
	fptr[7]=responseHandler;
#ifdef DEBUG
	printf("%s Ends\n",__func__);  
#endif
      return 0; 
}

