#include <func.h>
#define N 10000000
int main()
{
	int mid = shmget(1000,4096,IPC_CREAT|0600);
	if(-1 == mid)
	{
		perror("shmget");
		return -1;
	}
	int sem_id = semget(1000,1,IPC_CREAT|0600);
	printf("sem_id is:%d\n",sem_id);
	if(-1 == sem_id)
	{
		perror("semget");
		return -1;
	}
	int *p = (int*)shmat(mid,NULL,0);
	p[0] = 0;
	struct sembuf sopp,sopv;
	sopp.sem_num = 0;
	sopp.sem_op = -1;
	sopp.sem_flg = SEM_UNDO;
	sopv.sem_num = 0;
	sopv.sem_op = 1;
	sopv.sem_flg = SEM_UNDO;
	int ret = semctl(sem_id,0,SETVAL,1);
	if(-1 == ret)
	{
		perror("semctl");
		return -1;
	}
	if(!fork())
	{
		for (int i = 0; i < N;i++)
		{
			semop(sem_id,&sopp,1);
			p[0]++;
			semop(sem_id,&sopv,1);
		}
	 	exit(0);
	} else {
		for (int i = 0; i < N;i++)
		{
			semop(sem_id,&sopp,1);
			p[0]++;
			semop(sem_id,&sopv,1);
		}
		wait(NULL);
		printf("%d\n",p[0]);
		return 0;
	}
}
