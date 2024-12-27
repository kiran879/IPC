#include"../header.h"
#include"../keys.h"
#include"declaration.h"
#include"../client/dataStructures.h"
void* vendorsHandler(void *arg)
{
	int ret,fd,shmid,semID,sret,shm1id,shm2id;
	request *rqst;
	vendorResponse *shmptr;
	vendorResponse response;
	int *data;
	key_t sKey,key;
	sem_t *shm1ptr,*shm2ptr;
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
	//share memory for response writing
	key=ftok(filepath,shmKey);
	shmid=shmget(key,0,0666);
	if(shmid==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	
	shmptr=(vendorResponse*)shmat(shmid,NULL,0);
	//critical section. Semphore intializing
	/*
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
	*/
	//shared memory which has Posix semaphore3(initialized as 1) 
	key=ftok(filepath,shmSem2);
	shm1id=shmget(key,0,0666);
	if(shm1id==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shm1ptr=(sem_t*)shmat(shm1id,NULL,0);
	//shared memory which has Posix semaphore2(initialized as 0) 
	key=ftok(filepath,shmSem1);
	shm2id=shmget(key,0,0666);
	if(shm2id==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shm2ptr=(sem_t*)shmat(shm2id,NULL,0);
	sem_wait(shm1ptr);//sem1 wait operation, waits until previously written response in shm is read by the server's response handler
	
	*shmptr=response;//writing to the Shared Memory
	
	sem_post(shm2ptr);
	
	//end of critical section(shared memory write)
	/*
	sb[0].sem_op=1;//Increment semaphore
        sret=semop(semID,sb,1);//signal operation for semaphore 1
        if(sret==-1)
        {
		perror("semop");
		exit(EXIT_FAILURE);
 	}	
	*/
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
