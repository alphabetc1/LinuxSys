#include <func.h>
struct msgtype{
	long mtype;
	char buf[60];
};
int main(int argc, char **argv)
{//2号进程
       args_check(argc,1);
       char buf[128] = {0};
       fd_set fdrd;
       int wr = open("1.pipe",O_WRONLY);
       if(-1 == wr)
       {
              perror("open2");
              return -1;
       }
       int rd = open("2.pipe",O_RDONLY);
       if(-1 == rd)
       {
              perror("open1");
              return -1;
       }
       printf("i'm a writer\n");
	   int msgid = msgget((key_t)1000,0600 | IPC_CREAT);
	   if(-1 == msgid)
	   {
           perror("msgget");
           return -1;
	   }
	   struct msgtype msg;
       while(1)
       {
              FD_ZERO(&fdrd);
              FD_SET(STDIN_FILENO,&fdrd);
              FD_SET(rd,&fdrd);
              int ret = select(rd+1,&fdrd,NULL,NULL,NULL);
              if(ret > 0)
              {
				  memset(&msg,0,sizeof(msg));
				  memset(buf,0,sizeof(buf));
				  if(FD_ISSET(STDIN_FILENO,&fdrd))
				  {
					  ret = read(STDIN_FILENO,buf,sizeof(buf));
					  msg.mtype = 2;
					  memcpy(msg.buf,buf,strlen(buf)-1);
					  msgsnd(msgid,&msg,sizeof(msg.buf),0);
					  write(wr,buf,strlen(buf)-1);
				  }
				  if(FD_ISSET(rd,&fdrd))
				  {
					  ret = read(rd,buf,sizeof(buf));
					  if(0 == ret)
					  {
						  printf("byebye\n");
						  msg.mtype = 3;
						  break;
					  }
					  msg.mtype = 1;
					  memcpy(msg.buf,buf,strlen(buf));
					  msgsnd(msgid,&msg,sizeof(msg.buf),0);
					  //printf("%s\n",buf);
				  }
			  }else {
				  printf("timeout\n");
			  }
	   }
       return 0;
}
