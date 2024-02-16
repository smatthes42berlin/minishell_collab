#include "minishell.h"

bool	node_is_pipe(t_node *node)
{
	if (!node)
		return (false);
	return ((node->type) == PIPE);
}

bool	node_is_hdoc(t_node *node)
{
	if (!node)
		return (false);
	return ((node->type) == HEREDOC);
}

bool	node_is_exec(t_node *node)
{
	if (!node)
		return (false);
	return ((node->type) == EXEC);
}

bool	node_is_redir(t_node *node)
{
	if (!node)
		return (false);
	return ((node->type) == REDIR);
}
