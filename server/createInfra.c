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
	ipcs->sharedMid=*(int*)(*fptr[5])(0);
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)ipcs;
}
