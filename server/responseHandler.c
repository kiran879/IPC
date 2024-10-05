#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
#include"../client/dataStructures.h"
#include"../keys.h"
void* responseHandler(void *arg)
{
	serverResponse res;
	vendorResponse *shmptr;
	key_t key,sKey;
	int shmid,msgid,ret,semID,sret;
	struct sembuf sb[1];
#ifdef DEBUG
	printf("File:%s ->%s:Begins\n",__FILE__,__func__);
#endif
	key=ftok("shmfile",shmKey);
	shmid=shmget(key,0,0666);
	if(shmid==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shmptr=(vendorResponse*)shmat(shmid,NULL,0);
//      fgets(shmptr,sizeof(vendorResponse),&response);
       	printf("val in responseHandler:%d, %d\n",shmptr->result,shmptr->pid);
	res.pid=shmptr->pid;
	res.result=shmptr->result;
	key=ftok("msgQ",msgQKey);
	msgid=msgget(key,0666);
	sKey=ftok("semaphore",semKey);
	semID=semget(sKey,4,0666);
	if(semID==-1)
	{
		perror("semget");
		exit(1);
	}
	sb[0].sem_num=0;//assigning semaphore number
 	sb[0].sem_op=-1;//Decrement sem val
 	sb[0].sem_flg=0;
        sret=semop(semID,sb,1);//wait operation for sempahore 0
        if(sret==-1)
        {
		perror("semop");
	 	exit(EXIT_FAILURE);
	}
	ret=msgsnd(msgid,&res,sizeof(res.result),0);
	if(ret==-1)
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	 //end of critical section(fifo write)
        sb[0].sem_op=1;//Increment semapharoe
	sret=semop(semID,sb,1);//signal operation for semaphore 0
        if(sret==-1)
	{
		perror("semop");
                exit(EXIT_FAILURE);
        }


#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
