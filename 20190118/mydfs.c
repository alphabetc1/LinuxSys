#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#define get_argv(argc,num) {if(argc != num){printf("error");return -1;}}

void dfs(char *dirname, int num)
{
	DIR *pdir;
	char path[512] = {0};
	pdir = opendir(dirname);
	if(NULL == pdir)
	{
		perror("opendir");
		return ;
	}
	struct dirent *p;
	while ((p = readdir(pdir)) != NULL)
	{
		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))continue;
		printf("%*s%s\n",num," ", p->d_name);
		if(4 == p->d_type)
		{
			sprintf(path,"%s/%s",dirname,p->d_name);
			dfs(path, num + 4);
		}
	}
	closedir(pdir);
}

int main(int argc, char *argv[])
{
	get_argv(argc, 2);
	dfs(argv[1],4);
	return 0;
}


