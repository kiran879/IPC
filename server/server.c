#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* shutdownServer(void*);//extern int exitProgram(char*);
void* createInfra(void*);
void* createPipe(void*);
void* createFifo(void*);
void* createMsgQ(void*);
void* createSharedM(void*);
void* createSemaphore(void*);
void* requestHandler(void*);
void* responseHandler(void*);
int init();
void* (*fptr[NOF])(void*);
int main()
{
	IPCs *ipcs;
#ifdef DEBUG
	printf("File:%s ->%s:Begins\n",__FILE__,__func__);
#endif
	init();
	ipcs=(IPCs*)(*fptr[0])(0);//createInfra
	while(1)
	{
	printf("fifoname in server main:%s\n",ipcs->fifoName);
	(*fptr[6])((void*)ipcs);//requestHandler
	sleep(1);
	(*fptr[7])(0);//responseHandler
	}
#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
