#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
#include"../keys.h"
void* createSharedM(void *arg)
{
	IPCs *ipcs;
	key_t key,key2,key3,key4;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	ipcs=(IPCs*)arg;
	key=ftok(filepath,shmKey);
	ipcs->sharedM1=shmget(key,2000,0666|IPC_CREAT);
	if(ipcs->sharedM1==-1)
	{
		perror("shmget");
		exit(1);
	}
	printf("Shared Memory created successfully with id %d\n",ipcs->sharedM1);
	key2=ftok(filepath,shmSem1);
	printf("key val:%d\n",key2);
	ipcs->sharedM2=shmget(key2,50,0666|IPC_CREAT);
	if(ipcs->sharedM2==-1)
	{
		perror("shmget");
		exit(1);
	}
	printf("Shared Memory created successfully with id %d\n",ipcs->sharedM2);
	key3=ftok(filepath,shmSem2);
	printf("key val:%d\n",(int)key3);
	ipcs->sharedM3=shmget(key3,sizeof(sem_t),0666|IPC_CREAT);
	if(ipcs->sharedM3==-1)
	{
		perror("shmget");
		exit(1);
	}
	key4=ftok(filepath,shmSem3);
	ipcs->sharedM4=shmget(key4,sizeof(sem_t),0666|IPC_CREAT);
	if(ipcs->sharedM4==-1)
	{
		perror("shmget");
		exit(1);
	}
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)ipcs;
}
