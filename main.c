#include "shell.h"

int main(int argc, char* argv[])
{
    //欢迎界面
    printf("\n/------------------------------------\n");
    printf("  Welcome to Master of light shell !!\n");
    printf("  The current user is %s\n", user);
    printf("------------------------------------\\\n\n");

    mysh_loop();

    return 0;
}