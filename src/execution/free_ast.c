#include "minishell.h"

static void	free_exec(t_node *node);
static void	free_redim(t_node *node);
static void	free_pipe(t_node *node);

void	free_ast(t_node *node)
{
	// printf("I am Freeing \n");
	if (node->type == PIPE)
		free_pipe(node);
	else if (node->type == REDIR)
		free_redim(node);
	else if (node->type == EXEC)
		free_exec(node);
	// free(node);
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
	if (exec_node != NULL)
	{
		free_str_arr_null(exec_node->argv);
		free_str_arr_null(exec_node->env);
		free(exec_node->file_path);
		free(exec_node);
	}
	free(node);
	return ;
}

static void	free_redim(t_node *node)
{
	t_node_redir	*redir_node;

	redir_node = (t_node_redir *)node->node_type;
	if (redir_node != NULL)
	{
		free(redir_node->filename);
		if (redir_node->left_node != NULL)
			free_ast(redir_node->left_node);
		free(redir_node);
	}
	free(node);
}

static void	free_pipe(t_node *node)
{
	t_node_pipe	*pipe_node;

	pipe_node = (t_node_pipe *)node->node_type;
	if (pipe_node != NULL)
	{
		if (pipe_node->left_node != NULL)
			free_ast(pipe_node->left_node);
		if (pipe_node->right_node != NULL)
			free_ast(pipe_node->right_node);
		free(pipe_node);
	}
	free(node);
}