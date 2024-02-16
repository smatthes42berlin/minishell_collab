#include "minishell.h"

char	*add_newline(char *str, bool newline)
{
	char	*ret;

	ret = NULL;
	if (newline)
		ret = ft_strjoin(str, "\n");
	else
		ret = ft_strdup(str);
	return (ret);
}

char	**copy_str_arr(char **arg, int i_beginn, bool newline)
{
	int i_count;
	char **ret;
	char *str_tmp;

	i_count = i_beginn;
	while (arg[i_count] != NULL)
		i_count++;
	ret = malloc_handler(sizeof(char *) * (i_count - i_beginn + 1));
	ret[i_count - i_beginn] = NULL;
	i_count = i_beginn;
	while (arg[i_count] != NULL)
	{
		str_tmp = ft_strdup(arg[i_count]);
		if (newline)
			ret[i_count - i_beginn] = ft_strjoin(str_tmp, "\n");
		else
			ret[i_count - i_beginn] = ft_strdup(str_tmp);
		free(str_tmp);
		str_tmp = NULL;
		i_count++;
	}
	return (ret);
}