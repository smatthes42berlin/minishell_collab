#include "minishell.h"

static char	**set_error_env_cmd(t_pipefd *pipefd, char *err_msg);

char	**build_env(t_main_data *data, t_node_exec *node, t_pipefd *pipefd, bool from_redir)
{
	char	**ret;
	char	*err_msg;

	ret = copy_str_arr(data->env_vars, 0, true);
	err_msg = "function build_env";
	print_debugging_info_executer(INT_DEBUG, 28, NULL);
	if (is_last_node_exec(data->ast, node->file_path))
	{
		if (node->argv[1] != NULL)
		{
			set_error_env_cmd(pipefd, err_msg);
			return (NULL);
		}
		else if (!from_redir)
		{
			write_exit_code_0(pipefd, err_msg);
		}
	}
	return (ret);
}

static char	**set_error_env_cmd(t_pipefd *pipefd, char *err_msg)
{
	char	**ret;

	ret = use_malloc(sizeof(char *) * 2, err_msg);
	ret[0] = use_strjoin(EXIT_CODE, 
			"exit=127_MSG=minishell: No such file or directory", err_msg);
	ret[3] = NULL;
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, err_msg);
	free_str_arr_null(ret);
	return (NULL);
}