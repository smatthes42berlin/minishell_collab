#include "minishell.h"

static char	*last_node(t_node *node);
static char	*check_exec(t_node *node);
static char	*check_redir(t_node *node);
static char	*check_pipe(t_node *node);

bool	is_last_node_redir(t_node *node, char *filename)
{
	// char *compare_last = last_node(node);
	// printf("i check the is redir last \n|%s|\n|%s|\n", filename, compare_last);
	if (str_are_equal(last_node(node), filename))
	{
		return (true);
	}
	return (false);
}

static char	*last_node(t_node *node)
{
	char	*ret;

	ret = NULL;
	if (node->type == PIPE)
		ret = check_pipe(node);
	else if (node->type == REDIR)
		ret = check_redir(node);
	else if (node->type == EXEC)
		ret = check_exec(node);
	return (ret);
}

static char	*check_exec(t_node *node)
{
	t_node_exec	*exec_node;

	exec_node = (t_node_exec *)node;
	return (exec_node->file_path);
}

static char	*check_redir(t_node *node)
{
	t_node_redir	*redir_node;

	redir_node = (t_node_redir *)node;
	return (redir_node->filename);
}

static char	*check_pipe(t_node *node)
{
	t_node_pipe	*pipe_node;

	pipe_node = (t_node_pipe *)node;
	return (last_node(pipe_node->right_node));
}