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