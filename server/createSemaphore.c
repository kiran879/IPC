#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createSemaphore(void *arg)
{
	int *semID;
	int sret;
	key_t key;
	semun semUnion;
	struct sembuf sb[1];
	unsigned short s[4];
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	semID=(int*)malloc(sizeof(int));
	key=ftok("semaphore",semKey);
	*semID=semget(key,4,0666|IPC_CREAT);
	if(*semID==-1)
	{
		perror("semget");
		exit(1);
	}
	semUnion.val=1;
	sret=semctl(*semID,0,SETVAL,semUnion);
	if(sret==-1)
	{
		perror("semctl");
		exit(EXIT_FAILURE);
	}
	sret=semctl(*semID,1,SETVAL,semUnion);
	if(sret==-1)
	{
		perror("semctl");
		exit(EXIT_FAILURE);
	}
	sret=semctl(*semID,2,SETVAL,semUnion);
	if(sret==-1)
	{
		perror("semctl");
		exit(EXIT_FAILURE);
	}
	sret=semctl(*semID,3,SETVAL,semUnion);
	if(sret==-1)
	{
		perror("semctl");
		exit(EXIT_FAILURE);
	}
/*	sb[0].sem_num=0;
	sb[0].sem_op=1;
	sb[0].sem_flg=0;
	semop(*semID,sb,1);
*/	
	printf("Semaphore array with 4 semaphores created successfully with id %d\n",*semID);
	semUnion.array=s;
	semctl(*semID,0,GETALL,semUnion);
	printf("sem values: %d %d %d %d\n",s[0],s[1],s[2],s[3]);
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)semID;
}
