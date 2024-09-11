#include"../header.h"
//#include"declaration.h"
#include"dataStructures.h"
#include"../server/dataStructures.h"
#include"../keys.h"
//void* client1(void *arg)
int main()
{
	request rqst;
	int fd,wret,ret,msgid;
	char temp[10];
	serverResponse res;
	key_t key;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	fd=open("../server/Fifo",O_WRONLY);
	if(fd==-1)
	{
		perror("open");
		exit(1);
	}
	rqst.pid=getpid();
	//printf("Please enter the expression with two only operands\n");
	fgets(temp,10,stdin);
	rqst.a=temp[0]-'0';
	rqst.ch=temp[1];
	rqst.b=temp[2]-'0';
	printf("pid in client-%d\n",rqst.pid);
	wret=write(fd,&rqst,sizeof(request));
	if(wret==-1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	sleep(1);
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
