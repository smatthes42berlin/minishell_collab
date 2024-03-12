#include "minishell.h"

static int	exec_exist(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct, bool from_redir);
static int	use_execve(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct, bool from_redir);
static int	use_buildin(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct, bool from_redir);

int	type_exec(t_main_data *data, t_node *node, t_pipefd *pipe_struct,
		bool from_redir)
{
	t_node_exec	*exec_node;
	int			ret;

	ret = 0;
	if (node != NULL)
	{
		exec_node = (t_node_exec *)node;
		if (exec_node->file_path != NULL)
		{
			ret = exec_exist(data, exec_node, pipe_struct, from_redir);
		}
		else
		{
			ret = exec_null_error(data, exec_node, pipe_struct);
		}
	}
	else
		printf("💀 Given node to EXEC is NULL! 💀\n");
	return (ret);
}

static int	exec_exist(t_main_data *data, t_node_exec *exec_node,
		t_pipefd *pipe_struct, bool from_redir)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	pid = fork_handler("functtion type_exec -> filepath NULL");
	if (pid == 0)
	{
		if (restore_default_signals(SIGQUIT + SIGINT))
			exit(errno);
		ret = use_execve(data, exec_node, pipe_struct, from_redir);
		free_main_exit(data, 0);
		free(pipe_struct);
		if (ret == -1)
			exit(errno);
		else
			exit (ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		ret = get_process_exit_code(status);
	}
	return (ret);
}

static int	use_execve(t_main_data *data, t_node_exec *exec_node,
		t_pipefd *pipe_struct, bool from_redir)
{
	int	ret;

	ret = -1;
	if (false == exec_node->is_inbuilt)
	{
		if (execve_handler(exec_node->file_path,
				exec_node->argv, exec_node->env) < 0)
		{
			free_main_exit(data, 0);
			free(pipe_struct);
			exit(errno);
		}
	}
	else
	{
		ret = use_buildin(data, exec_node, pipe_struct, from_redir);
	}
	return (ret);
}

static int	use_buildin(t_main_data *data, t_node_exec *exec_node,
		t_pipefd *pipe_struct, bool from_redir)
{
	char	**temp_str;
	int		i_count;

	temp_str = chose_buildin(data, exec_node, pipe_struct);
	if (((is_last_node_exec(data->ast, exec_node->file_path) || from_redir)
			&& (temp_str != NULL)))
	{
		i_count = 0;
		while (temp_str[i_count] != NULL)
		{
			ft_printf("%s", temp_str[i_count++]);
		}
	}
	free_str_arr_null(temp_str);
	return (pipe_struct->exit_code_buildin);
}
