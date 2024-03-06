#include "minishell.h"

static char	*checking_exit(t_node_exec *exec_node, int *exit_code);
static char	*checking_path(t_node_exec *exec_node, int *exit_code);

void	exec_null_error(t_node_exec *exec_node, t_pipefd *pipe_struct)
{
	pid_t	pid;
	char	*tmp_str;
	int		status;
	int		exit_code;

	pid = fork_handler("functtion type_exec -> filepath NULL");
	if (pid == 0)
	{
		tmp_str = checking_exit(exec_node, &exit_code);
		throw_error_mimic_bash(tmp_str, exit_code);
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
	else if (exec_node->argv[0][0] == '.')
	{
		if (execve_handler(exec_node->argv[0], exec_node->argv,
				exec_node->env) < 0)
		{
			ret = use_strjoin(exec_node->argv[0], ": Permission denied",
					"use_strjoin");
			*exit_code = 127;
		}
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

	ret = NULL;
	if (chdir(exec_node->argv[0]) >= 0)
	{
		ret = use_strjoin(exec_node->argv[0], ": Is a directory",
				"use_strjoin");
		*exit_code = 126;
	}
	else
	{
		if (access_handler(exec_node->argv[0], FILE_EXISTS, 0) >= 0)
		{
			ret = use_strjoin(exec_node->argv[0], ": Permission denied",
					"use_strjoin");
			*exit_code = 126;
		}
		else
		{
			ret = use_strjoin(exec_node->argv[0], ": No such file or directory",
					"use_strjoin");
			*exit_code = 127;
		}
	}
	return (ret);
}
