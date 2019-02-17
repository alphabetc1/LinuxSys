#include <func.h>

int main()
{
	int shmid = shmget(1000,4096,IPC_CREAT | 0600);
	if(-1 == shmid)
	{
		perror("shmget");
		return -1;
	}
	int shmct = shmget(1001,4096,IPC_CREAT | 0600);
	if(-1 == shmct)
	{}
	char *p = (char*)shmat(shmid,NULL,0);
	int *q = (int *)shmat(shmct,NULL,0);
	char buf[128];
	while(1)
	{
		memset(buf,0,128);
		if(3 == q[0])
			return 0;
		else if(1 == q[0])
		{
			memcpy(buf,p,strlen(p));
			printf("Hanmei:%-20s\n",buf);
			q[0] = 0;
		}else if(2 == q[0])
		{
			memcpy(buf,p,strlen(p));
			printf("Lilei:%20s\n",buf);
			q[0] = 0;
		}
	
	}
}
