#include "minishell.h"

static void	free_exec(t_node *node);
static void	free_redim(t_node *node);
static void	free_pipe(t_node *node);

void	free_ast(t_node *node)
{
	//printf("I am Freeing \n");
	if (node->type == PIPE)
		free_pipe(node);
	else if (node->type == REDIR)
		free_redim(node);
	else if (node->type == EXEC)
		free_exec(node);
	free(node);
}

void	free_str_arr_tes(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
}

static void	free_exec(t_node *node)
{
	t_node_exec	*exec_node;

	exec_node = (t_node_exec *)node->node_type;
	printf("Delet %s\n", exec_node->name_exec);
	free_str_arr_null(exec_node->argv);
	free_str_arr_null(exec_node->env);
	free(exec_node->file_path);
	free(exec_node->name_exec);
	//free(exec_node);
	return ;
}

static void	free_redim(t_node *node)
{
	t_node_redir	*redim_node;

	redim_node = (t_node_redir *)node->node_type;
	free(redim_node->filename);
	free(redim_node->name_redir);
	free_exec(redim_node->child_node);
	free(redim_node);
	return ;
}

static void	free_pipe(t_node *node)
{
	t_node_pipe *pipe_node;
	int pipefd[2];
	pid_t main_pid;
	pid_t nested_pid;

	pipe_node = (t_node_pipe *)node->node_type;
	printf("Delet %s\n", pipe_node->name_Pipe);
	pipe_handler(pipefd);
	main_pid = fork_handler();
	if (main_pid == 0)
	{
		free_exec(pipe_node->left_node);
		//free_ast(pipe_node->left_node);
		free(pipe_node->left_node);
	}
	else
	{
		pipe_setting(pipefd, false, NULL);
		nested_pid = fork_handler();
		if (nested_pid == 0)
		{
			free_exec(pipe_node->right_node);
			// free_ast(pipe_node->right_node);
			 free(pipe_node->right_node);
		}
		else
		{
			waitpid(main_pid, NULL, 0);
			waitpid(nested_pid, NULL, 0);
		}
	}
	//free(pipe_node);
}