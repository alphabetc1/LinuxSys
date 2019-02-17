#include <stdio.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#define get_argv(argc,num) {if(argc != num){printf("error");return -1;}}

int main(int argc, char **argv)
{
	get_argv(argc,2);
	DIR *pdir;
 	pdir=opendir(argv[1]);
	int ret, mode,i, k;
	char time[200],fmode[20];
	struct dirent *p;
	struct stat buf;
	struct passwd *my_info;

 	if(NULL==pdir)
	{
		perror("opendir");
		return 0;
 	}
	while((p = readdir(pdir))!=NULL){

		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")) 
		{
			continue;
		}
		i = 0, k = 512;
		printf("%d\n", ret);
		my_info = getpwuid(buf.st_uid);
		mode = buf.st_mode;
		memset(fmode,0,10);
		if(S_ISDIR(mode))
		{
			fmode[i] = 'd';
		}else {
			fmode[i] = '-';
		}
		i++;
		mode = mode % k;
		k = k / 2;
		while (mode)
		{
			if(mode / k == 0)
			{
				fmode[i++] = '-';
			}	
			else {
				if(i%3 == 1)fmode[i++] = 'r';
				else if(i%3 ==2)fmode[i++] = 'w';
				else fmode[i++] = 'x';
			}
			mode = mode %k;
			k = k/2;
		}
		while(i<10)fmode[i++] = '-';
		fmode[i] = 0;

		strncpy(time,ctime(&buf.st_atime),20);
		printf("%s %ld %s %s %6ld %s %s\n",fmode,buf.st_nlink,my_info->pw_name,my_info->pw_name,buf.st_size,time,p->d_name);
	}
	return 0;
}

