#include <func.h>
//1号进程
int main(int argc, char **argv)
{
       args_check(argc,1);
       char buf[128] = {0};
       fd_set fdrd;
       int rd = open("1.pipe",O_RDONLY);//读1
       if(-1 == rd)
       {
              perror("open1");
              return -1;
       }
       int wr = open("2.pipe",O_WRONLY);//写2
       if(-1 == wr)
       {
              perror("open2");
              return -1;
       }
       printf("i'm a reader\n");

	   int shmid = shmget(1000,4096,IPC_CREAT);		
	   if(-1 == shmid)
       {
           perror("shmget");
           return -1;
       }						
	   int shmct = shmget(1001,4096,IPC_CREAT);
	   if(-1 == shmct)
       {
           perror("shmget");
           return -1;
       }						
	   char *p = (char*)shmat(shmid,NULL,0);
	   int *q = (int*)shmat(shmct,NULL,0);
	   q[0] = 0;

       while(1)
       {
              FD_ZERO(&fdrd);
              FD_SET(STDIN_FILENO,&fdrd);
              FD_SET(rd,&fdrd);
              int ret = select(rd+1,&fdrd,NULL,NULL,NULL);
              if(ret > 0)
              {
                    memset(buf,0,sizeof(buf));
	   				memset(p,0,4096);
              		if(FD_ISSET(STDIN_FILENO,&fdrd))
                    {
                        ret = read(STDIN_FILENO,buf,sizeof(buf));
						memcpy(p,buf,strlen(buf)-1);
						q[0] = 1;
                        write(wr,buf,strlen(buf)-1);
                     }
                     if(FD_ISSET(rd,&fdrd))    
                     {
                        ret = read(rd,buf,sizeof(buf));
                        if(0 == ret)               
                        {
							printf("byebye\n");
							q[0] = 3;
							break;
						}
						memcpy(p,buf,strlen(buf));
						q[0] = 2;
						//printf("%s\n",buf);
                     }
			  }else {
	   			  printf("timeout\n");
              }
       }
       return 0;
}
