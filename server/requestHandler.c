#include"../header.h"
#include"declaration.h"
#include"../server/dataStructures.h"
#include"../client/dataStructures.h"
void* requestHandler(void *arg)
{
	IPCs *ipcs;
	request *rqst;
	int pid,wret,ret,rfd=0,semID,sret;
	key_t sKey;
	char fd[4];
	struct sembuf sb[1];
#ifdef DEBUG
	printf("File:%s ->%s:Begins\n",__FILE__,__func__);
#endif
	rqst=(request*)malloc(sizeof(request));
	if(!rqst)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ipcs=(IPCs*)(arg);
	printf("fifo name: %s\n",ipcs->fifoName);
	rfd=open(ipcs->fifoName,O_RDONLY);
	if(rfd==-1)
	{
		perror("open");	
 		exit(EXIT_FAILURE);
	}
	sKey=ftok("semaphore",semKey);
	semID=semget(sKey,4,0666);
	if(semID==-1)
	{
		perror("semget");
		exit(1);
	}
	sb[0].sem_num=1;//assigning semaphore number
 	sb[0].sem_op=-1;//Decrement sem val
	sb[0].sem_flg=0;
	printf("test befor read in req handler\n");
	ret=read(rfd,rqst,sizeof(request));
	if(ret==-1)
	{
		perror("read");
 		exit(EXIT_FAILURE);
 	}
//	close(rfd);
 	printf("%c\n",rqst->ch);
 	printf("Testing %d\n",rqst->a);
 	printf("Testing client pid:%d\n",rqst->pid);

	if(rqst->ch == '+' || rqst->ch == '-' || rqst->ch == '*' || rqst->ch == '/')
	{
		pid=fork();
		if(pid==0)
		{
			sret=semop(semID,sb,1);//wait operation for sempahore 0
			wret=write(*ipcs->pipes+1,rqst,sizeof(request));
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
			sprintf(fd,"%d",*ipcs->pipes);
			ret=execl("../vendors/vendorOperations","vendorOperations",fd,NULL);
			if(ret==-1)
			{
				perror("execl");
				exit(EXIT_FAILURE);
			}
			/*
		
			switch(rqst->ch)
			{
				case '+':
					wret=write(*ipcs->pipes+1,rqst,sizeof(request));
					if(wret==-1)
					{
						perror("write");
						exit(EXIT_FAILURE);
					}
					sprintf(fd,"%d",*ipcs->pipes);
					ret=execl("../vendors/vendorMain","vendorMain",fd,NULL);
					if(ret==-1)
					{
						perror("execl");
						exit(EXIT_FAILURE);
					}
					break;
			} */
		}
	}
	else //write down into the message queue for invalid request, as the client is block on read for the result
	{
		printf("Invalid Request\n");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
