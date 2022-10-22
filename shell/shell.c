#include "shell.h"

//函数指针数组
int(*builtin_func[])(char**) = {
    &mysh_cd,
    &mysh_help,
    &mysh_ls,
    &mysh_exit,
    &mysh_whoami,
    &mysh_rename
};

int mysh_launch(char** args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execv(args[1], args) == -1) {
            perror("Mysh error at execv\n");
        }
        exit(EXIT_FAILURE);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && WIFSIGNALED(status));
    }

    return 1;
}

char* mysh_read_line()
{
    char* line = NULL;
    ssize_t buffer_size;
    getline(&line, &buffer_size, stdin);

    return line;
}

char** mysh_split_line(char* line)
{
    int buffer_size = MYSH_BUFFER_SIZE, position = 0;
    char** tokens = malloc(buffer_size * sizeof(char*));
    char* token = NULL;

    token = strtok(line, MYSH_TOK_DELIM);

    while (token != NULL) {
        tokens[position++] = token;
        token = strtok(NULL, MYSH_TOK_DELIM);
    }
    tokens[position] = NULL;

    return tokens;
}

int mysh_extuce(char** args)
{
    if (args[0] == NULL) {
        return 1;
    }
    //由用户输入的命令来判断调用哪个函数
    for (int i = 0; i < builtin_nums(); i++) {
        if (strcmp(args[0], builtin_cmd[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return mysh_launch(args);
}

void mysh_loop()
{
    char* line;
    char** args;

    int status;

    do {
        char path[100];
        getcwd(path, 100);  //得到当前所在目录

        char now[200] = "[";
        strcat(now, "\e[32m");
        //用户名
        strcat(now, user);
        strcat(now, "@MASTER-OF-LIGHT:\e[0m");
        strcat(now, "\e[34m");
        strcat(now, path);
        strcat(now, "\e[0m");
        strcat(now, "]$");
        //打印用户、当前路径
        printf("%s", now);

        //获取用户输入参数
        line = mysh_read_line();
        args = mysh_split_line(line);
        status = mysh_extuce(args);

        free(line);
        free(args);
    } while (status);
}