#include "minishell.h"

char *add_newline(char *str, bool newline)
{
    char *ret;

    ret = NULL;
	if (newline)
		ret = ft_strjoin(str, "\n");	
	else
		ret = ft_strdup(str);
    return (ret);
}

char **copy_str_arr(char **arg, int i_beginn)
{
    int i_count;
    char **ret;

    i_count = i_beginn;
   // printf("i count |%d| -- |%d|\n", i_count, i_beginn);
    while(arg[i_count] != NULL)
        i_count++;
   // printf("i count |%d| -- |%d| Malloc size |%d|\n", i_count, i_beginn, i_count - i_beginn + 1);
    ret = malloc_handler(sizeof(char *) * (i_count - i_beginn + 1));
    ret[i_count - i_beginn] = NULL;
    i_count = i_beginn;
    while(arg[i_count] != NULL)
    {   
        ret[i_count-i_beginn] = ft_strdup(arg[i_count]);
        i_count++;
    }
    return(ret);
}