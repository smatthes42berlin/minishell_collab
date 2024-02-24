#include "minishell.h"

static void	add_clr_command_to_arr_str(char **arg);

char	**build_unset(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	print_debugging_info_executer(INT_DEBUG, 27, NULL);
	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	ret = copy_str_arr(node->argv, 1, false);
	add_clr_command_to_arr_str(ret);
	print_str_arr_null(ret);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
	//pipe_setting(pipefd->pipefd, true, ret, "function \"build_unset\"");
	return (NULL);
}

static void	add_clr_command_to_arr_str(char **arg)
{
	int		i_count;
	char	*tmp_str;

	i_count = 0;
	while (arg[i_count] != NULL)
	{
		tmp_str = ft_strdup(arg[i_count]);
		free(arg[i_count]);
		arg[i_count] = NULL;
		arg[i_count] = ft_strjoin(CLR_ENV, tmp_str);
		free(tmp_str);
		tmp_str = NULL;
		i_count++;
	}
}
