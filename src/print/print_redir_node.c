#include "minishell.h"

int	print_redir_node(t_node_redir *node, int mode)
{
	if (mode == 0)
	{
		printf("Redir %s", node->filename);
		printf(" %d", node->mode);
		printf(" %d", node->in_or_out);
	}
	else
	{
		printf("\n***********************************\n");
		printf("REDIR NODE\n");

		if (mode >= 2)
		{
			printf("parent_node: %p\n", node->parent_node);
			printf("left_node: %p\n", node->left_node);
			printf("right_node: %p\n", node->right_node);
		}
		printf("mode: %d\n", node->mode);
		printf("in_or_out: %d\n", node->in_or_out);
		printf("filename: %s\n", node->filename);
	}
	return (0);
}