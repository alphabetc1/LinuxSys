#include "func.h"

typedef struct msgtype{
	long mtype;
	char buf[50];
}msgtype;

int main()
{
	int msgid = msgget((key_t)1000,IPC_CREAT|0600);
	if(-1 == msgid)
	{
		perror("msgget");
		return -1;
	}
	msgtype msg;
	memset(&msg,0,sizeof(struct msgtype));
	if(!fork())
	{
		sleep(1);
		msg.mtype = 1;
		msgrcv(msgid,&msg,sizeof(msg.buf),2,0);
		puts(msg.buf);
		exit(0);
	}else {
		msg.mtype = 2;
		strcpy(msg.buf,"hello");
		msgsnd(msgid,&msg,sizeof(msg.buf),0);	
		wait(NULL);
		msgctl(msgid,IPC_RMID,NULL);
		return 0;
	}
}
