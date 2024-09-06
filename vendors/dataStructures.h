typedef struct
{
	int* pipes;
	char* fifoName;
	int msgQid;
	int sharedMid;
}IPCs;
typedef struct
{
	long int pid;
	int result;
}serverResponse;

