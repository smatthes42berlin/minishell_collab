#include "minishell.h"

int	print_exec_node(t_node_exec *node, int mode)
{
	if (mode == 0)
		printf("Exec: %s", node->file_path);
	else
	{
		printf("\n***********************************\n");
		printf("EXEC NODE\n");
		if (mode >= 2)
		{
			printf("parent_node: %p\n", node->parent_node);
			printf("left_node: %p\n", node->left_node);
			printf("right_node: %p\n", node->right_node);
		}
		printf("filepath: %s\n", node->file_path);
		printf("is_inbuilt: %d\n", node->is_inbuilt);
		printf("args: \n");
		print_str_arr_null(node->argv);
	}
	return (0);
}
