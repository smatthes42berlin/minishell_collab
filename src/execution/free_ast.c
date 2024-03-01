#include "minishell.h"

static void	free_exec(t_node *node);
static void	free_redim(t_node *node);
static void	free_pipe(t_node *node);
static void	free_heredoc(t_node *node);

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	if (node->type == PIPE)
		free_pipe(node);
	else if (node->type == REDIR)
		free_redim(node);
	else if (node->type == EXEC)
		free_exec(node);
	else if (node->type == HEREDOC)
		free_heredoc(node);
	node = NULL;
}

static void	free_exec(t_node *node)
{
	t_node_exec	*exec_node;

	exec_node = (t_node_exec *)node;
	if (exec_node != NULL)
	{
		free_str_arr_null(exec_node->argv);
		exec_node->argv = NULL;
		free_str_arr_null(exec_node->env);
		exec_node->env = NULL;
		free(exec_node->file_path);
		exec_node->file_path = NULL;
		free(exec_node);
		exec_node = NULL;
	}
	return ;
}

static void	free_redim(t_node *node)
{
	t_node_redir	*redir_node;

	redir_node = (t_node_redir *)node;
	if (redir_node != NULL)
	{
		if (redir_node->filename != NULL)
		{
			free(redir_node->filename);
			redir_node->filename = NULL;
		}
		if (redir_node->left_node != NULL)
			free_ast(redir_node->left_node);
		free(redir_node);
		redir_node = NULL;
	}
}

static void	free_pipe(t_node *node)
{
	t_node_pipe	*pipe_node;

	pipe_node = (t_node_pipe *)node;
	if (pipe_node != NULL)
	{
		if (pipe_node->left_node != NULL)
			free_ast(pipe_node->left_node);
		if (pipe_node->right_node != NULL)
			free_ast(pipe_node->right_node);
		free(pipe_node);
		pipe_node = NULL;
	}
}

static void	free_heredoc(t_node *node)
{
	t_node_heredoc *heredoc_node;

	heredoc_node = (t_node_heredoc *)node;
	if (heredoc_node != NULL)
	{
		if (heredoc_node->left_node != NULL)
			free_ast(heredoc_node->left_node);
		free(heredoc_node);
		heredoc_node = NULL;
	}
}
