typedef struct
{
	int* pipes;
	char* fifoName;
	int msgQid;
	int sharedMid;
	int semID;
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

