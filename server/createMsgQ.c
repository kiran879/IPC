#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createMsgQ(void *arg)
{
	int *msgid;
	key_t key;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
	msgid=(int*)malloc(sizeof(int));
	key=ftok("msgQ",msgQKey);
	*msgid=msgget(key,0666|IPC_CREAT);
	if(*msgid==-1)
	{
		perror("msgget");
		exit(1);
	}
	printf("Message Queue created successfully with id %d\n",*msgid);
#endif
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return (void*)msgid;
}
