#include "minishell.h"

void	type_exec(t_node *node)
{
	t_node_exec	*exec_node;

	exec_node = check_buildin(node);
	if (NULL == exec_node)
	{
		exec_node = (t_node_exec *)node->node_type;
		execve_handler(exec_node->file_path, exec_node->argv, exec_node->env);
	}
	else
		printf("%s\n", chose_buildin(exec_node));
}

// void	type_redim(t_node *node)
// {
// 	t_node_redir	*redir_node;
// 	pid_t			pid;
// 	int				fd;
// 	int				pipefd[2];

// 	redir_node = (t_node_redir *)node->node_type;
// 	pid = fork_handler();
// 	pipe_handler(pipefd);
// 	if (pid == 0)
// 	{
// 		pipe_setting(pipefd,true,NULL);
// 		fd = open_handler(redir_node->filename, redir_node->mode);
// 		dup2(fd, redir_node->in_or_out);
// 		close(fd);

// 		//navigate_tree_forward(redir_node->child_node)
// 	}
// 	else{
// 		pipe_setting(pipefd,false,NULL);
// 		navigate_tree_forward(redir_node->child_node);
// 		waitpid(pid, NULL, 0);
// 	}
// }

void	type_redim(t_node *node)
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
	navigate_tree_forward(redir_node->child_node);
}

void	type_pipe(t_node *node)
{
	t_node_pipe *pipe_node;
	int pipefd[2];
	pid_t main_pid;
	pid_t nested_pid;

	pipe_node = (t_node_pipe *)node->node_type;
	pipe_handler(pipefd);
	main_pid = fork_handler();
	if (main_pid == 0)
	{
		if (false == check_and_choose_buildin(pipe_node->left_node, pipefd,
				true))
		{
			// printf("\n\n NO inbuild LEFT SIDE!\n\n");
			pipe_setting(pipefd, true, NULL);
			navigate_tree_forward(pipe_node->left_node);
		}
	}
	else
	{
		pipe_setting(pipefd, false, NULL);
		nested_pid = fork_handler();
		if (nested_pid == 0)
		{
			if (false == check_and_choose_buildin(pipe_node->right_node, pipefd,
					false))
			{
				// printf("\n\n NO inbuild Rigt SIDE!\n\n");
				navigate_tree_forward(pipe_node->right_node);
			}
		}
		else
		{
			waitpid(main_pid, NULL, 0);
			waitpid(nested_pid, NULL, 0);
		}
	}
}