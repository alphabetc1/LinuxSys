#include <func.h>

struct MSG{
	long mtype;
	char buf[64];
}MSG;
int main()
{
	int msgid = msgget((key_t)1000,0600 | IPC_CREAT);
	if(-1 == msgid)
	{
	}
	struct MSG msg;
	memset(&msg,0,sizeof(msg));
	while(1)
	{
		msgrcv(msgid,&msg,sizeof(msg.buf),0,0);
		if(3 == msg.mtype)
			return 0;
		else if(1 == msg.mtype)
		{
			printf("Hanmei:%20s\n",msg.buf);
			msg.mtype = 0;
		}else if(2 == msg.mtype)
		{
			printf("Lilei:%-20s\n",msg.buf);
			msg.mtype = 0;
		}
	}
	
}
