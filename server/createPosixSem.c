#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createPosixSem(void *arg)
{
	sem_t *semID,*shm2,*shm3,*shm4;
	IPCs *ipcs;
	int sret;
	key_t key;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	ipcs=(IPCs*)arg;
	semID=(sem_t*)malloc(sizeof(sem_t));
	if(!semID)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	sret=sem_init(&ipcs->pSemID,0,1);
	if(sret==-1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	shm2=(sem_t*)shmat(ipcs->sharedM2,NULL,0);
	sret=sem_init(shm2,1,0);
	if(sret==-1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	shm3=(sem_t*)shmat(ipcs->sharedM3,NULL,0);
	sret=sem_init(shm3,1,1);
	if(sret==-1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	shm4=(sem_t*)shmat(ipcs->sharedM4,NULL,0);
	sret=sem_init(shm4,1,1);
	if(sret==-1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	printf("Posix Semaphore is sucessfully created for server thread synchronization\n");
	//posix sem for message queue send/recieve synchronization
	
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)semID;
}
