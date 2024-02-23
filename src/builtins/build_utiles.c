#include "minishell.h"

char	*add_newline(char *str, bool newline)
{
	char	*ret;

	ret = NULL;
	if (newline)
		ret = ft_strjoin(str, "\n");
	else
		ret = ft_strdup(str);
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"add_newline\" for \'\' command!"});
	return (ret);
}

static char **creat_str_arr(char **arg, int i_beginn)
{
	int i_count;
	char **ret;

	i_count = i_beginn;
	while (arg[i_count] != NULL)
		i_count++;
	ret = malloc(sizeof(char *) * (i_count - i_beginn + 1));
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"creat_str_arr\" for \'copy_str_arr\' function"});
	ret[i_count - i_beginn] = NULL;
	return (ret);
}

char	**copy_str_arr(char **arg, int i_beginn, bool newline)
{
	int i_count;
	char **ret;
	char *str_tmp;

	ret = creat_str_arr(arg, i_beginn);
	i_count = i_beginn;
	while (arg[i_count] != NULL)
	{
		str_tmp = ft_strdup(arg[i_count]);
		if (!str_tmp)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
				"function \"copy_str_arr\""});
		if (newline)
			ret[i_count - i_beginn] = ft_strjoin(str_tmp, "\n");
		else
			ret[i_count - i_beginn] = ft_strdup(str_tmp);
		if (!ret[i_count - i_beginn])
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
				"function \"copy_str_arr\""});
		free(str_tmp);
		str_tmp = NULL;
		i_count++;
	}
	return (ret);
}