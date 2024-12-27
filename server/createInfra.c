#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createInfra(void *arg)
{
	IPCs *ipcs;
	int fd,ret;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	ipcs=(IPCs*)malloc(sizeof(IPCs));
	ipcs->pipes=(int*)(*fptr[2])(0);//createPipe
	printf("Pipe successfullly created with FDs: read:%d and write:%d\n",*ipcs->pipes,*ipcs->pipes+1);
	ipcs->fifoName=(char*)(*fptr[3])(0);
	ipcs->msgQid=*(int*)(*fptr[4])(0);
	(*fptr[5])((void*)ipcs);//create Shared Memory
	ipcs->semID=*(int*)(*fptr[8])(0);
	/*ipcs->pSemID=*(int*)*/(*fptr[9])((void*)ipcs);
	printf("testing sharedM %d,%d,%d,%d\n",ipcs->sharedM1,ipcs->sharedM2,ipcs->sharedM3,ipcs->sharedM4);
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)ipcs;
}
