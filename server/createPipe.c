#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createPipe(void *arg)
{
	IPCs ipcs;
	int ret;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
	ipcs.pipes=(int*)malloc(sizeof(int)*2);
	if(!ipcs.pipes)
	{
		perror("malloc");
		exit(1);
	}
	ret=pipe(ipcs.pipes);
	if(ret==-1)
	{
		perror("pipe");
		free(ipcs.pipes);
		exit(1);
	}
#endif
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)ipcs.pipes;
}
