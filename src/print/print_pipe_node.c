#include "minishell.h"

int	print_pipe_node(t_node_pipe *node, int mode)
{
	if (mode == 0)
		printf("Pipe");
	else
	{
		printf("\n***********************************\n");
		printf("PIPE NODE\n");
		if (mode >= 2)
		{
			printf("parent_node: %p\n", node->parent_node);
			printf("left_node: %p\n", node->left_node);
			printf("right_node: %p\n", node->right_node);
		}
	}
	return (0);
}