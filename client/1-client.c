#include"../header.h"
//#include"declaration.h"
#include"dataStructures.h"
#include"../server/dataStructures.h"
#include"../keys.h"
//void* client1(void *arg)
int main()
{
	request rqst;
	int fd,wret,ret,msgid,semID,sret;
	char temp[10];
	serverResponse res;
	key_t key,sKey;
	struct sembuf sb[1];
	unsigned short val[1];
	semun su;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	//preparing the request
	rqst.a=5;
	rqst.b=6;
	rqst.ch='*';
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
	su.array=val;
	semctl(semID,0,GETALL,su);
	printf("sem val:%d and semid:%d\n",val[0],semID);
	//start of critical section(open fifo for write mode)
	sret=semop(semID,sb,1);//wait operation for sempahore 0
	if(sret==-1)
	{
		perror("semop");
		exit(EXIT_FAILURE);
	}
	fd=open("../server/Fifo",O_WRONLY);
	if(fd==-1)
	{
		perror("open");
		exit(1);
	}
	rqst.pid=getpid();
	printf("pid in client-%d\n",rqst.pid);
	wret=write(fd,&rqst,sizeof(request));
	if(wret==-1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	//end of critical section(fifo write)
	sb[0].sem_op=1;//Increment semaphore
	sret=semop(semID,sb,1);//signal operation for semaphore 0
	if(sret==-1)
	{
		perror("semop");
		exit(EXIT_FAILURE);
	}
//	close(fd);
	key=ftok("msgQ",msgQKey);
	msgid=msgget(key,0666);
	ret=msgrcv(msgid,&res,sizeof(res.result),getpid(),0);
	if(ret==-1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("Result:%d\n",res.result);
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
