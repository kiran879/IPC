#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createSharedM(void *arg)
{
	int *shmid;
	key_t key;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	key=ftok("shmfile",50);
	shmid=(int*)malloc(sizeof(int));
	*shmid=shmget(key,2000,0666|IPC_CREAT);
	if(*shmid==-1)
	{
		perror("shmget");
		exit(1);
	}
	printf("Shared Memory created successfully with id %d\n",*shmid);
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)shmid;
}
