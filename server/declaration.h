#include"../keys.h"
#define NOF 8
extern void* createInfra(void*);
//extern void* shutdownServer(void*);//extern int exitProgram(char*);
extern void* createPipe(void*);
int init();
extern void* createFifo(void*);
extern void* createMsgQ(void*);
extern void* createSharedM(void*);
extern void* requestHandler(void*);
extern void* responseHandler(void*);
extern void* (*fptr[NOF])(void*);
