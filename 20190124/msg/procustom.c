#include <func.h>
#define N 10000000
int main()
{
	int semArr_id = semget(1000,2,IPC_CREAT|0600);
	if(-1 == semArr_id)
	{
		perror("semget");
		return -1;
	}
	printf("semArr_id is:%d\n",semArr_id);
	unsigned short arr[2] = {10,0};
	struct sembuf sopp,sopv;
	int ret = semctl(semArr_id,0,SETALL,arr);
	if(-1 == ret)
	{
		perror("semctl");
		return -1;
	}
	if(!fork())
	{
		sopp.sem_num = 1;
		sopp.sem_op = -1;
		sopp.sem_flg = SEM_UNDO;
		sopv.sem_num = 0;
		sopv.sem_op = 1;
		sopv.sem_flg = SEM_UNDO;
		while(1)
		{
			printf("Customer\n");
			printf("now:%d %d\n",semctl(semArr_id,0,GETVAL),semctl(semArr_id,1,GETVAL));
			semop(semArr_id,&sopp,1);	
			semop(semArr_id,&sopv,1);
			printf("now:%d %d\n",semctl(semArr_id,0,GETVAL),semctl(semArr_id,1,GETVAL));
			sleep(2);
		}
	 	exit(0);
	} else {
		sopp.sem_num = 0;
		sopp.sem_op = -1;
		sopp.sem_flg = SEM_UNDO;
		sopv.sem_num = 1;
		sopv.sem_op = 1;
		sopv.sem_flg = SEM_UNDO;
		while(1)
		{
			printf("Producer\n");
			printf("now:%d %d\n",semctl(semArr_id,0,GETVAL),semctl(semArr_id,1,GETVAL));
			semop(semArr_id,&sopp,1);	
			semop(semArr_id,&sopv,1);
			printf("now:%d %d\n",semctl(semArr_id,0,GETVAL),semctl(semArr_id,1,GETVAL));
			sleep(1);
		}
		wait(NULL);
		return 0;
	}
}
