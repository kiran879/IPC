#include"../header.h"
#include"declaration.h"
void* shutdownServer(void*);//extern int exitProgram(char*);
void* createInfra(void*);
void* createPipe(void*);
void* createFifo(void*);
int init();
void* (*fptr[NOF])(void*);
int main()
{
#ifdef DEBUG
	printf("File:%s ->%s:Begins\n",__FILE__,__func__);
#endif
	init();
	(*fptr[0])(0);
#ifdef DEBUG
	printf("File:%s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
