#include "minishell.h"

static void	replace_env_in_str_arr(t_main_data *data, char **arg);
static char	*str_arr_to_str(char **str, bool newline);

char	**build_echo(t_main_data *data, t_node_exec *node)
{
	char	**ret;
	char	**tmp_str_1;
	bool	newline;
	int		i_beginn_cp;

	tmp_str_1 = NULL;
	i_beginn_cp = 1;
	newline = false;
	print_debugging_info_executer(INT_DEBUG, 23, NULL);
	if (!ft_strcmp(node->argv[1], "-n"))
	{
		i_beginn_cp = 2;
		newline = true;
	}
	tmp_str_1 = copy_str_arr(node->argv, i_beginn_cp, false);
	replace_env_in_str_arr(data, tmp_str_1);
	ret = malloc(sizeof(char *) * 2);
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"build_echo\" for \'echo\' command!"});
	ret[0] = str_arr_to_str(tmp_str_1, !newline);
	ret[1] = NULL;
	free_str_arr_null(tmp_str_1);
	return (ret);
}

static void	replace_env_in_str_arr(t_main_data *data, char **arg)
{
	int		i_count;
	char	*tmp_str;

	i_count = 0;
	while (arg[i_count] != NULL)
	{
		if (arg[i_count][0] == '$' && arg[i_count][1] != '\0'
			&& arg[i_count] != NULL)
		{
			tmp_str = ft_strdup(arg[i_count]);
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = env_get_var(data, tmp_str);
			free(tmp_str);
			tmp_str = NULL;
		}
		else if (arg[i_count][0] == '$' && arg[i_count][1] != '?'
			&& arg[i_count] != NULL)
		{
			//printf("exitcode ist echo command |%i|\n", data->exit_code);
			//tmp_str = ft_strjoin(ft_itoa(data->exit_code), arg[i_count] + 2);
			arg[i_count] = NULL;
			arg[i_count] = ft_strdup(tmp_str);
			free(tmp_str);
			tmp_str = NULL;
		}
		i_count++;
	}
}

static char	*creat_str_leng(int total_length, int i)
{
	char	*tmp_str;

	tmp_str = malloc(sizeof(char) * (total_length + i + 1));
	if (!tmp_str)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"absoult_or_relativ_path\" for \'cd\' command!"});
	tmp_str[0] = '\0';
	return (tmp_str);
}

static char	*str_arr_to_str(char **str, bool newline)
{
	size_t	total_length;
	char	*tmp_str;
	char	*ret;
	int		i;

	total_length = 0;
	i = 0;
	while (str[i] != NULL)
		total_length += ft_strlen(str[i++]);
	tmp_str = creat_str_leng(total_length, i);
	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '\0')
		{
			ft_strlcat(tmp_str, str[i], total_length + i + 1);
			if (str[i + 1] != NULL)
				ft_strlcat(tmp_str, " ", total_length + i + 1);
		}
		i++;
	}
	ret = add_newline(tmp_str, newline);
	free(tmp_str);
	return (ret);
}
