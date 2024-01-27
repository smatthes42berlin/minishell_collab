#include "minishell.h"

char *build_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        error_code_handler(errno, "ERR-getcwd", "", "");
    return (cwd);
    //printf("Current directory: %s\n", cwd);
    //free(cwd);
}

void *choose_buildin(char *cmd)
{
    if (cmd == "pwd")
    {
        return ((char *)build_pwd());
    }
    return (NULL);
}