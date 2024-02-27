#include "minishell.h"

static void	check_equal_sign_in_str_arr(char **arg);

char	**build_export(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	print_debugging_info_executer(INT_DEBUG, 26, NULL);
	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	ret = copy_str_arr(node->argv, 1, false);
	check_equal_sign_in_str_arr(ret);
	//print_str_arr_null(ret);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret,
		"function \"build_export\"");
	// pipe_setting(pipefd->pipefd, true , ret, "function \"buid_export\"");
	return (NULL);
}

static void	check_equal_sign_in_str_arr(char **arg)
{
	int		i_count;
	char	*tmp_str;

	i_count = 0;
	while (arg[i_count] != NULL)
	{
		//printf("Given export %s,\n",arg[i_count]);
		//tmp_str = ft_strtrim(arg[i_count], ft_strchr(arg[i_count], '=') + 1);
		if (!check_bash_variable(arg[i_count]))
		{
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = ft_strjoin(EXIT_CODE,
					"exit=1_MSG=minishell: export: not a valid identifier");
			return ;
		}
		if (ft_strchr(arg[i_count], '=') == NULL)
		{
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = "";
			return ;
		}
		else
		{	free(tmp_str);
			tmp_str = NULL;
			tmp_str = ft_strdup(arg[i_count]);
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = ft_strjoin(ADD_ENV, tmp_str);
			free(tmp_str);
			tmp_str = NULL;
		}
		i_count++;
	}
}
