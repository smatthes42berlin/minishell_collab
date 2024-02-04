#include "minishell.h"

void	navigate_tree_forward(t_main_data *data, t_node *node)
{
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation no node", "", "");
	if (node->type == PIPE)
		type_pipe(data, node);
	else if (node->type == REDIR)
		type_redim(data, node);
	else if (node->type == EXEC)
		type_exec(data, node);
	else
		printf("No Nodetype found\n");
}
