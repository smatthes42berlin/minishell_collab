#include "minishell.h"

void	type_exec(t_node *node)
{
	t_node_exec	*exec_node;

	exec_node = (t_node_exec *)node->node_type;
	//printf("Node %s\n", exec_node->name_exec);
	execve_handler(exec_node->file_path, exec_node->argv, exec_node->env);
}

void	type_redim(t_node *node)
{
	t_node_redir	*redir_node;
	int				fd;

	redir_node = (t_node_redir *)node->node_type;
	//printf("Node %s\n", redir_node->name_redir);
	fd = open_handler(redir_node->filename, redir_node->mode);
	dup2(fd, redir_node->in_or_out);
	close(fd);
	navigate_tree_forward(redir_node->child_node);
}

void	type_pipe(t_node *node)
{
	t_node_pipe *pipe_node;
	int pipefd[2];
	pid_t main_pid;
	pid_t nested_pid;

	pipe_node = (t_node_pipe *)node->node_type;
	//printf("Node %s\n", pipe_node->name_Pipe);
	pipe_handler(pipefd);
	main_pid = fork_handler();
	if (main_pid == 0)
	{
		pipe_setting(pipefd, true);
		navigate_tree_forward(pipe_node->left_node);
	}
	else
	{
		pipe_setting(pipefd, false);
		nested_pid = fork_handler();
		if (nested_pid == 0)
			navigate_tree_forward(pipe_node->right_node);
		else
		{
			waitpid(main_pid, NULL, 0);
			waitpid(nested_pid, NULL, 0);
		}
	}
}