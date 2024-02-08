#include "minishell.h"

int	init_generic_node_param(t_node *node, enum e_node_type type)
{
	node->type = type;
	node->parent_node = NULL;
	node->left_node = NULL;
	node->right_node = NULL;
	return (0);
}

