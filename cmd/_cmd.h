#ifndef __CMD_H
#define __CMD_H

#include<unistd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include<dirent.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define USER_NAME_SIZE   20

#define MYSH_TOK_DELIM  " \t\r\n"
#define MYSH_BUFFER_SIZE  64

#define ERROR_OK   1
#define ERROR_FAIL 0

extern char user[USER_NAME_SIZE];
extern char* builtin_cmd[];

//命令函数
int mysh_cd(char** args);
int mysh_help(char** args);
int mysh_ls(char** args);

int mysh_whoami(char** args);
int mysh_rename(char** args);

int mysh_exit(char** args);

int builtin_nums();

#endif /* __CMD_H */