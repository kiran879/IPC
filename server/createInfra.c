#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createInfra(void *arg)
{
	IPCs ipcs;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	ipcs.pipes=(*fptr[2])(0);//createPipe
	printf("Pipe successfullly created with FDs: read:%d and write:%d\n",*ipcs.pipes,*ipcs.pipes+1);
	ipcs.fifoName=(*fptr[3])(0);
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
