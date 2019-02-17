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
