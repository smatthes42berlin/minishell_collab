#include "minishell.h"

static char	*last_node(t_node *node);
static char	*check_exec(t_node *node);
static char	*check_redir(t_node *node);
static char	*check_pipe(t_node *node);

bool	is_last_node_exec(t_node *node, char *path)
{
	if (str_are_equal(last_node(node), path))
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
	return (last_node(redir_node->left_node));
}

static char	*check_pipe(t_node *node)
{
	t_node_pipe	*pipe_node;

	pipe_node = (t_node_pipe *)node;
	return (last_node(pipe_node->right_node));
}
