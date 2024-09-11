#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
#include"../client/dataStructures.h"
void* responseHandler(void *arg)
{
	serverResponse res;
	vendorResponse *shmptr;
	key_t key;
	int shmid,msgid,ret;
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
	ret=msgsnd(msgid,&res,sizeof(res.result),0);
	if(ret==-1)
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
