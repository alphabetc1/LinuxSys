#include <func.h>

void handle(int num,siginfo_t *pInfo,void *p)
{
	printf("Signal %d is coming\n",num);
}

int main()
{
	sigset_t set,test;
	memset(&set,0,sizeof(set));
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,NULL);
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction = handle;
	act.sa_flags = SA_RESTART | SA_SIGINFO ;
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
	sleep(5);
	sigpending(&test);
	if(sigismember(&test,SIGINT))
	{
		printf("Yes\n");
	}else 
		printf("No\n");

	sigprocmask(SIG_UNBLOCK,&set,NULL);
	return 0;
}
