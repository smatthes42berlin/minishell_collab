#include "minishell.h"

int	print_hdoc_node(t_node_heredoc *node, int mode)
{
	if (mode == 0)
		printf("Hdoc fd = %d", node->read_fd);
	else
	{
		printf("\n***********************************\n");
		printf("HDOC NODE\n");
		if (mode >= 2)
		{
			printf("parent_node: %p\n", node->parent_node);
			printf("left_node: %p\n", node->left_node);
			printf("right_node: %p\n", node->right_node);
		}
		printf("read_fd: %d\n", node->read_fd);
		printf("is_last_node: %d\n", node->is_last_node);
	}
	return (0);
}
