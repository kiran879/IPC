typedef struct
{
	int* pipes;
	char* fifoName;
	int msgQid;
	int sharedM1;
	int sharedM2;
	int sharedM3;
	int sharedM4;
	int semID;
	sem_t pSemID;
}IPCs;
typedef struct
{
	long int pid;
	int result;
}serverResponse;
typedef union
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
}semun;

