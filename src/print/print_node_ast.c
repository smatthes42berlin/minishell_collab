#include "minishell.h"

int	print_node_ast(t_node *node)
{
	if (!node)
		return (0);
	if (node->type == EXEC)
		return (print_exec_node((t_node_exec *)node, 1));
	if (node->type == PIPE)
		return (print_pipe_node((t_node_pipe *)node, 1));
	if (node->type == REDIR)
		return (print_redir_node((t_node_redir *)node, 1));
	if (node->type == HEREDOC)
		return (print_hdoc_node((t_node_heredoc *)node, 1));
	return (0);
}
