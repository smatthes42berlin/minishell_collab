#include "minishell.h"

void	type_exec(t_node *node)
{
	t_node_exec	*exec_node;
	char		*file_path;
	char		**argv;
	char		**env;

	exec_node = (t_node_exec *)node->node_type;
	file_path = exec_node->file_path;
	argv = exec_node->argv;
	env = exec_node->env;
	free(node);
	execve_handler(file_path, argv, env);
}

void	type_redim(t_node *node, t_list *pid_list)
{
	t_node_redir	*redir_node;
	pid_t			pid;
	int				fd;

	redir_node = (t_node_redir *)node->node_type;
	pid = fork_handler();
	if (pid == 0)
	{
		fd = open_handler(redir_node->filename, redir_node->mode);
		dup2(fd, redir_node->in_or_out);
		close(fd);
		navigate_tree_forward(redir_node->child_node, &pid_list);
	}
	else
		waitpid(pid, NULL, 0);
}

void	redim_exec_check(t_node *node, t_list *pid_list)
{
	if (node->type == REDIR)
		type_redim(node, pid_list);
	else if (node->type == EXEC)
		type_exec(node);
	else
		printf("No Nodetype found\n");
}

void	nested_fork_parent(t_node *left, t_node *right, t_list *pid_list)
{
	pid_t	nested_pid;

	if (left->type == PIPE)
		navigate_tree_forward(left, &pid_list);
	if (right->type == REDIR || right->type == EXEC)
	{
		nested_pid = fork_handler();
		if (nested_pid == 0)
			redim_exec_check(right, pid_list);
		else
			waitpid(nested_pid, NULL, 0);
	}
	else
		navigate_tree_forward(right, &pid_list);
}

void	type_pipe(t_node *node, t_list **pid_list)
{
	t_node_pipe	*pipe_node;
	int			pipefd[2];
	pid_t		pid;

	pipe_node = (t_node_pipe *)node->node_type;
	pipe_handler(pipefd);
	pid = fork_handler();
	if (pid == 0)
	{
		pipe_setting(pipefd, true);
		redim_exec_check(pipe_node->left_node, *pid_list);
	}
	else
	{
		append_node_pid_list(pid_list, pid);
		pipe_setting(pipefd, false);
		nested_fork_parent(pipe_node->left_node, pipe_node->right_node,
			*pid_list);
	}
}