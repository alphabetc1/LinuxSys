#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#define get_argv(argc,num) {if(argc != num){printf("error");return -1;}}
//遍历所给目录查找目标文件，有则返回绝对路径

void dfs(char *dirname, char *fname)
{
	DIR *pdir;
	char path[512] = {0};
	pdir = opendir(dirname);
	if(NULL == pdir)
	{
		//perror("opendir");
		return ;
	}
	
	struct dirent *p;
	while ((p = readdir(pdir)) != NULL)
	{

		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))continue;	
		if(!strcmp(p->d_name, fname))
		{
			chdir(dirname);
			getcwd(path,512);
			printf("%s/%s\n", path,fname);
			return;
		}
		if(4 == p->d_type)
		{
			dfs(p->d_name, fname);
		}
	}
	closedir(pdir);
}

int main(int argc, char *argv[])
{
	get_argv(argc, 3);
	dfs(argv[1],argv[2]);
	return 0;
}


