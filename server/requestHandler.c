#include"../header.h"
#include"declaration.h"
#include"../server/dataStructures.h"
#include"../client/dataStructures.h"
void* requestHandler(void *arg)
{
	IPCs *ipcs;
	request *rqst;
	int pid,wret,ret,rfd;
	char fd[4];
#ifdef DEBUG
	printf("File:%s ->%s:Begins\n",__FILE__,__func__);
#endif
	rqst=(request*)malloc(sizeof(request));
	ipcs=(IPCs*)(arg);
	rfd=open(ipcs->fifoName,O_RDONLY);
	if(rfd==-1)
	{
		perror("open");	
 		exit(EXIT_FAILURE);
	}
	ret=read(rfd,rqst,sizeof(request));
	if(ret==-1)
	{
		perror("read");
 		exit(EXIT_FAILURE);
 	}
 	printf("%c\n",rqst->ch);
	pid=fork();
	if(pid==0)
	{
		
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
		}
	}

#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
