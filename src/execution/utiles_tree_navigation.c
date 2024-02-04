#include "minishell.h"

static void type_pipe_nested_pid(t_main_data *data, t_node_pipe *pipe_node,  pid_t main_pid, int *pipefd);

void	type_exec(t_main_data *data, t_node *node)
{
	t_node_exec	*exec_node;
	char	*temp_str;

	exec_node = check_buildin(node);
	if (NULL == exec_node)
	{
		exec_node = (t_node_exec *)node->node_type;
		execve_handler(exec_node->file_path, exec_node->argv, exec_node->env);
	}
	else
		temp_str = chose_buildin(data, exec_node);
	if ((data->ast->type == REDIR || data->ast->type == EXEC) && temp_str != NULL)
		printf("%s\n", temp_str);
	free(temp_str);
}

void	type_redim(t_main_data *data, t_node *node)
{
	t_node_redir	*redir_node;
	int				fd;

	redir_node = (t_node_redir *)node->node_type;
	fd = open_handler(redir_node->filename, redir_node->mode);
	if (fd == -1)
	{
		error_code_handler(errno, "ERR-open_handler in \"type_redim\"", "", "");
		return ;
	}
	if (dup2(fd, redir_node->in_or_out) == -1)
	{
		close_handler(fd);
		error_code_handler(errno, "ERR-dub_2 in \"type_redim\"", "", "");
		return ;
	}
	close_handler(fd);
	navigate_tree_forward(data, redir_node->child_node);
}

void	type_pipe(t_main_data *data, t_node *node)
{
	t_node_pipe *pipe_node;
	int pipefd[2];
	//int pipefd_env[2];
	pid_t main_pid;
	
	pipe_node = (t_node_pipe *)node->node_type;
	pipe_handler(pipefd);
	main_pid = fork_handler();
	if (main_pid == 0)
	{
		if (false == check_and_choose_buildin(data, pipe_node->left_node, pipefd,
				true))
		{
			pipe_setting(pipefd, true, NULL);
			navigate_tree_forward(data, pipe_node->left_node);
		}
	}
	else
	{
		type_pipe_nested_pid(data, pipe_node, main_pid, pipefd);
	}
}


static void type_pipe_nested_pid(t_main_data *data, t_node_pipe *pipe_node, pid_t main_pid, int *pipefd)
{
		pid_t nested_pid;

		pipe_setting(pipefd, false, NULL);
		nested_pid = fork_handler();
		if (nested_pid == 0)
		{
			if (false == check_and_choose_buildin(data, pipe_node->right_node, pipefd,
					false))
			{
				navigate_tree_forward(data, pipe_node->right_node);
			}
		}
		else
		{
			waitpid(main_pid, NULL, 0);
			waitpid(nested_pid, NULL, 0);
		}
}