#include <func.h>

void handle(int num,siginfo_t *pInfo,void *p)
{
	printf("before winter %d is coming\n",num);
	sleep(3);
	sigset_t set;
	sigpending(&set);
	if(sigismember(&set,SIGQUIT))
	{
		printf("SIGQUIT is pending\n");
	}else 
		printf("SIGQUIT is not pending\n");
	printf("after winter %d is coming\n",num);
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction = handle;
	act.sa_flags = SA_RESTART;
	sigaddset(&act.sa_mask,SIGQUIT);
	int ret = sigaction(SIGINT,&act,NULL);
	if(-1 == ret)
	{
		perror("sigaction");
		return -1;
	}
	ret = sigaction(SIGQUIT,&act,NULL);
	if(-1 == ret)
	{
		perror("sigaction");
		return -1;
	}
	while(1);
	return 0;
}
