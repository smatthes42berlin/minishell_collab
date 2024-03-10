#include "minishell.h"

static char	**set_error_env_cmd(t_pipefd *pipefd, char *err_msg, char *arg);

char	**build_env(t_main_data *data, t_node_exec *node,
	t_pipefd *pipefd)
{
	char	**ret;
	char	*err_msg;

	ret = copy_str_arr(data->env_vars, 0, true);
	err_msg = "function build_env";
	if (is_last_node_exec(data->ast, node->file_path))
	{
		if (node->argv[1] != NULL)
		{
			set_error_env_cmd(pipefd, err_msg, node->argv[1]);
			return (NULL);
		}
		else
			pipefd->exit_code_buildin = 0;
		// else if (!from_redir)
		// {
		// 	write_exit_code_0(pipefd, err_msg);
		// }
	}
	return (ret);
}

static char	**set_error_env_cmd(t_pipefd *pipefd, char *err_msg, char *arg)
{
	char	**ret;
	char	*str_tmp_1;
	char	*str_tmp_2;

	ret = use_malloc(sizeof(char *) * 2, err_msg);
	str_tmp_1 = use_strjoin(EXIT_CODE, "_MSG=env: \'", err_msg);
	str_tmp_2 = use_strjoin(str_tmp_1, arg, err_msg);
	ret[0] = use_strjoin(str_tmp_2, "\': No such file or directory", err_msg);
	ret[1] = NULL;
	free(str_tmp_1);
	free(str_tmp_2);
	pipefd->exit_code_buildin = 127;
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, err_msg);
	free_str_arr_null(ret);
	return (NULL);
}
