#define NOF 4
extern void* createInfra(void*);
//extern void* shutdownServer(void*);//extern int exitProgram(char*);
extern void* createPipe(void*);
int init();
extern void* createFifo(void*);
extern void* (*fptr[NOF])(void*);
