#include"../header.h"
#include"declaration.h"
void* vendor2(void *arg)
{
	int *data,*result;
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	result=(int*)malloc(sizeof(int));
	data=(int*)arg;
	*result=*data - *(data+1);
	return (void*)result;
#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
