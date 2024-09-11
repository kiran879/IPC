#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createFifo(void *arg)
{
	IPCs ipcs;
	int ret;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
	ipcs.fifoName="Fifo";
	/*if(!ipcs.fifoName)
	{
		perror("malloc");
		exit(1);
	}*/
	ret=mkfifo(ipcs.fifoName,0666);
	if(ret==-1)
	{
		if(errno==17)
		{
			printf("Fifo already exist with name: %s, proceed further using it\n",ipcs.fifoName);
			return (void*)ipcs.fifoName;
		}
		else
		{
			perror("pipe");
			exit(1);
		}
	}
	printf("Fifo created successfully with name %s\n",ipcs.fifoName);
#endif
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)ipcs.fifoName;
}
