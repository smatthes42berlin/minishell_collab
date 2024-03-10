#include "minishell.h"

static void	add_clr_command_to_arr_str(char **arg);

char	**build_unset(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	ret = copy_str_arr(node->argv, 0, false);
	add_clr_command_to_arr_str(ret);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
	free_str_arr_null(ret);
	return (NULL);
}

static void	add_clr_command_to_arr_str(char **arg)
{
	int		i_count;
	char	*tmp_str;
	char	*err_msg;

	i_count = 1;
	err_msg = "function add_clr_command_to_arr_str -> build unset";
	while (arg[i_count] != NULL)
	{
		tmp_str = use_strdup(arg[i_count], err_msg);
		free(arg[i_count]);
		arg[i_count] = NULL;
		arg[i_count] = use_strjoin(CLR_ENV, tmp_str, err_msg);
		free(tmp_str);
		tmp_str = NULL;
		i_count++;
	}
}
