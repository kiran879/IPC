#include"../header.h"
#include"../keys.h"
#include"declaration.h"
#include"../client/dataStructures.h"
void* vendorsHandler(void *arg)
{
	int ret,fd,key,shmid,semID,sret;
	request *rqst;
	vendorResponse *shmptr;
	vendorResponse response;
	int *data;
	key_t sKey;
	struct sembuf sb[1];
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	rqst=(request*)malloc(sizeof(request));
	fd=*(int*)(arg);
	data=(int*)malloc(sizeof(int)*2);
	printf("pipe read:%d, in Vendors:%d\n",fd,getpid());
        ret=read(fd,rqst,sizeof(request));
        if(ret==-1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	*data=rqst->a;
	*(data+1)=rqst->b;
	switch(rqst->ch)
	{
		case '+':
			response.result= *(int*)(*fptr[2])((void*)data);
			break;
		case '-':
			response.result= *(int*)(*fptr[3])((void*)data);	
			break;
		case '*':
			response.result= *(int*)(*fptr[4])((void*)data);
			break;
		case '/':
			response.result= *(int*)(*fptr[5])((void*)data);
			break;
	}
	response.pid=rqst->pid;
	key=ftok("shmfile",shmKey);
	shmid=shmget(key,0,0666);
	if(shmid==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shmptr=(vendorResponse*)shmat(shmid,NULL,0);
	//critical section. Semphore intializing
	sKey=ftok("semaphore",semKey);
	semID=semget(sKey,4,0666);
	if(semID==-1)
	{
		perror("semget");
		exit(1);
	}
	sb[0].sem_num=2;//assigning semaphore number
        sb[0].sem_op=-1;//Decrement sem val
        sb[0].sem_flg=0;
        sret=semop(semID,sb,1);//wait operation for sempahore 2
        if(sret==-1)
        {
		perror("semop");
		exit(EXIT_FAILURE);
 	}

	*shmptr=response;//writing to the Shared Memory
	
	//end of critical section(shared memory write)
	sb[0].sem_op=1;//Increment semaphore
        sret=semop(semID,sb,1);//signal operation for semaphore 1
        if(sret==-1)
        {
		perror("semop");
		exit(EXIT_FAILURE);
 	}	

#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
