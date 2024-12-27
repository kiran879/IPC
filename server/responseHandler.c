#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
#include"../client/dataStructures.h"
#include"../keys.h"
void* responseHandler(void *arg)
{
	IPCs *ipcs;
	serverResponse res;
	vendorResponse *shmptr;
	key_t key,sKey;
	int shmid,msgid,ret,semID,sret,shm1id,shm2id;
	struct sembuf sb[1];
	sem_t *shm1ptr,*shm2ptr;
#ifdef DEBUG
	printf("File:%s ->%s:Begins\n",__FILE__,__func__);
#endif
	ipcs=(IPCs*)arg;
	key=ftok(filepath,shmKey);
	shmid=shmget(key,0,0666);
	if(shmid==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	printf("testing sharedM1 %d\n",ipcs->sharedM1);
	shmptr=(vendorResponse*)shmat(shmid,NULL,0);
	//getting msdqid, semid
	key=ftok("msgQ",msgQKey);
	msgid=msgget(key,0666);
	sKey=ftok("semaphore",semKey);
	semID=semget(sKey,4,0666);
	if(semID==-1)
	{
		perror("semget");
		exit(1);
	}
	//assigning values for sembuf
	sb[0].sem_num=2;//assigning semaphore number
 	sb[0].sem_flg=0;
//      fgets(shmptr,sizeof(vendorResponse),&response);
	
	//shared memory which has Posix semaphore2(initialized as 0) 
	key=ftok(filepath,shmSem1);
	shm2id=shmget(key,0,0666);
	if(shm2id==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shm2ptr=(sem_t*)shmat(shm2id,NULL,0);
	//shared memory which has Posix semaphore3(initialized as 1) 
	key=ftok(filepath,shmSem2);
	shm1id=shmget(key,0,0666);
	if(shm1id==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shm1ptr=(sem_t*)shmat(shm1id,NULL,0);

       	while(1)
	{

		sem_wait(shm2ptr);//sem2 wait operation, waits until a response is written in shm by the vendors
		printf("val in responseHandler:%d, %d\n",shmptr->result,shmptr->pid);
		res.pid=shmptr->pid;
		res.result=shmptr->result;
 		/*
		sb[0].sem_op=-1;//Decrement sem val
        	sret=semop(semID,sb,1);//wait operation for sempahore 0
        	if(sret==-1)
        	{
			perror("semop");
		 	exit(EXIT_FAILURE);
		}
		*/
		ret=msgsnd(msgid,&res,sizeof(res.result),0);
		if(ret==-1)
		{
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
		sem_post(shm1ptr);//sem post for the vendor to proceed with another thread in writing into the shm
		 //end of critical section(fifo write)
        	/*
		sb[0].sem_op=1;//Increment semapharoe
		sret=semop(semID,sb,1);//signal operation for semaphore 0
        	if(sret==-1)
		{
			perror("semop");
        	        exit(EXIT_FAILURE);
        	}
		*/
	}


#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
