#include "minishell.h"

static char	*checking_exit(t_node_exec *exec_node, int *exit_code);
static char	*checking_path(t_node_exec *exec_node, int *exit_code);

void	exec_null_error(t_main_data *data, t_node_exec *exec_node,
	t_pipefd *pipe_struct)
{
	pid_t	pid;
	char	*tmp_str;
	int		status;
	int		exit_code;

	if (data->ast == NULL)
		printf("NO AST FOUND!\n");
	pid = fork_handler("functtion type_exec -> filepath NULL");
	if (pid == 0)
	{
		if (restore_default_signals(SIGQUIT + SIGINT))
			exit(errno);
		tmp_str = checking_exit(exec_node, &exit_code);
		throw_error_mimic_bash(tmp_str, exit_code);
		free(tmp_str);
		free_main_exit(pipe_struct->main_data, 0);
		free(pipe_struct);
		exit(exit_code);
	}
	else
	{
		waitpid(pid, &status, 0);
		write_exit_status_to_pipe(status, pipe_struct, "err");
	}
}

static char	*checking_exit(t_node_exec *exec_node, int *exit_code)
{
	char	*ret;

	ret = NULL;
	if (ft_strchr(exec_node->argv[0], '/') != NULL)
	{
		return (checking_path(exec_node, exit_code));
	}
	else if ((access_handler(exec_node->argv[0], FILE_EXECUTABLE, 0) < 0)
		|| exec_node->is_folder == true)
	{
		ret = use_strjoin(exec_node->argv[0], ": command not found",
				"use_strjoin");
		*exit_code = 127;
	}
	return (ret);
}

static char	*checking_path(t_node_exec *exec_node, int *exit_code)
{
	char	*ret;
	char	*str_tmp;
	char	*err_msg;

	ret = NULL;
	err_msg = "type_exec -> filepath = NULL";
	str_tmp = use_strjoin("minishell: ", exec_node->argv[0], err_msg);
	*exit_code = 126;
	if (chdir(exec_node->argv[0]) >= 0)
		ret = use_strjoin(str_tmp, ": Is a directory", err_msg);
	else
	{
		if (access_handler(exec_node->argv[0], FILE_EXISTS, 0) >= 0)
			ret = use_strjoin(str_tmp, ": Permission denied", err_msg);
		else
		{
			ret = use_strjoin(str_tmp, ": No such file or directory", err_msg);
			*exit_code = 127;
		}
	}
	free(str_tmp);
	return (ret);
}
