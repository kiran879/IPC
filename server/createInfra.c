#include"../header.h"
#include"declaration.h"
#include"dataStructures.h"
void* createInfra(void *arg)
{
#ifdef DEBUG
	printf("File: %s ->%s:Begins\n",__FILE__,__func__);
#endif
	(*fptr[2])(0);	


#ifdef DEBUG
	printf("File: %s ->%s:Ends\n",__FILE__,__func__);
#endif

	return 0;
}
