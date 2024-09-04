#include"../header.h"
#include"declaration.h"
void* vendorsHandler(void*);
void* vendor1(void*);
void* vendor2(void*);
void* vendor3(void*);
void* vendor4(void*);
int init();
void* (*fptr[NOF])(void*);
int main(int argc,char* argv[])
{
	int *fd;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	init();
	fd=(int*)malloc(sizeof(int));
	*fd=atoi(argv[1]);
	printf("vendor's fd:%d\n",*fd);
	(*fptr[1])((void*)fd);

#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
