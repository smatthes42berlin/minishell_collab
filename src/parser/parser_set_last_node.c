#include "minishell.h"

int	parser_set_last_node(t_node *ast)
{
	t_node	*last_node;

	if (ast->right_node)
		last_node = ast->right_node;
	else
		last_node = ast;
	while (last_node->left_node)
		last_node = last_node->left_node;
	last_node->is_last_node = true;
	return (0);
}
