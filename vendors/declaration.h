#define NOF 6
//extern void* shutdownServer(void*);//extern int exitProgram(char*);
extern void* vendorsHandler(void*);
extern void* vendor1(void*);
extern void* vendor2(void*);
extern void* vendor3(void*);
extern void* vendor4(void*);
int init();
extern void* (*fptr[NOF])(void*);
