/*
    控制台文字上色的方法：
    demo: printf("\e[30m\e[41m Hello World \e[0m \n"); //红色字体，黑色背景

    使用"\e[0m"序列将颜色重新设置为正常值
   /-----------------------------------------------------------------------------/
    \e[30m – \e[37m 设置前景色(字体颜色)
    字符	                                            颜色
    30	                                                黑色
    31	                                                红色
    32	                                                绿色
    33	                                                黄色
    34	                                                蓝色
    35	                                                紫色
    36	                                                深绿
    37	                                                白色

    \e[40m – \e[47m 设置背景色
    字符                                                 颜色
    40	                                                 黑色
    41	                                                 红色
    42	                                                 绿色
    43	                                                 黄色
    44	                                                 蓝色
    45	                                                 紫色
    46	                                                 深绿
    47	                                                 白色
*/
#include "_cmd.h"

//用户名，默认名字为"hao",支持更改，最长支持20个字符
char user[USER_NAME_SIZE] = "hao";

//目前支持的命令
char* builtin_cmd[] = {
    "cd",
    "help",
    "ls",
    "exit",
    "whoami",    //查看当前用户
    "rename"
};

//实现命令
int mysh_cd(char** args)
{
    if (args[1] == NULL) {
        perror("Mysh error at cd, lack of args\n");
    } else {
        //chdir 是C语言中的一个系统调用函数（同cd），用于改变当前工作目录，其参数为Path 目标目录，
        //可以是绝对目录或相对目录。
        if (chdir(args[1]) != 0) {
            perror("Mysh error at chdir\n");
        }
    }

    return ERROR_OK;
}

//实现 ls 命令
int mysh_ls(char** args)
{
    DIR* dp = NULL;
    struct dirent* dt = NULL;

    //如果 ls 后面没有路径，则认为查看的是当前目录下
    if (args[1] == NULL) {
        dp = opendir("./");
    } else {
        dp = opendir(args[1]);
    }
    if (dp == NULL) {
        perror("opendir err\n");
    }

    while (1) {
        dt = readdir(dp);

        if (dt == NULL) {
            break;
        }
        if (dt->d_name[0] != '.')
            printf("\e[33m\e[40m %s \e[0m \n", dt->d_name);
    }
    closedir(dp);

    return ERROR_OK;
}

//输出当前用户名
int mysh_whoami(char** args)
{
    if (args[1] != NULL) {
        perror("Whoami behind with parameters\n");
        return ERROR_OK;
    }
    printf("\e[33m\e[40m %s \e[0m \n", user);
    return ERROR_OK;
}

int mysh_rename(char** args)
{
    if (args[1] == 0) {
        perror("Mysh error at rename, lack of args\n");
    } else if (sizeof(args[1]) > USER_NAME_SIZE) {
        perror("The new name is too long");
    } else {
        strcpy(user, args[ERROR_OK]);
        printf("Rename the success\n");
    }

    return ERROR_OK;
}

int mysh_help(char** args)
{
    puts("Welcome to Master of light shell !!");
    puts("Here are some bulit in cmd:");

    for (int i = 0; i < builtin_nums(); i++) {
        printf("\e[33m\e[40m %s \e[0m \t", builtin_cmd[i]);
    }
    printf("\n");
    puts("-----------------------------------");
    return ERROR_OK;
}

int mysh_exit(char** args)
{
    return ERROR_FAIL;
}

//共有几条指令
int builtin_nums()
{
    return sizeof(builtin_cmd) / sizeof(builtin_cmd[0]);
}