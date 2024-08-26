#define NOF 3
extern void* createInfra(void*);
//extern void* shutdownServer(void*);//extern int exitProgram(char*);
extern void* createPipe(void*);
int init();
extern void* (*fptr[NOF])(void*);
