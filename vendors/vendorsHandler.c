#include"../header.h"
#include"../keys.h"
#include"declaration.h"
#include"../client/dataStructures.h"
void* vendorsHandler(void *arg)
{
	int ret,fd,key,shmid;
	request *rqst;
	vendorResponse *shmptr;
	vendorResponse response;
	int *data;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	rqst=(request*)malloc(sizeof(request));
	fd=*(int*)(arg);
	data=(int*)malloc(sizeof(int)*2);
	printf("pipe read:%d",fd);
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
	*shmptr=response;//writing to the Shared Memory
	

#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
