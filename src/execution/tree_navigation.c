#include "minishell.h"

int	navigate_tree_forward(t_main_data *data, t_node *node,
		t_pipefd *pipe_struct)
{
	int	ret;

	ret = 0;
	if (node == NULL)
		printf("In function \"navigate_tree_forward\" (node == NULL) \n");
	if (node->type == PIPE)
		ret = type_pipe(data, node, pipe_struct);
	else if (node->type == REDIR)
		type_redir(data, node, pipe_struct);
	else if (node->type == EXEC)
		type_exec(data, node, pipe_struct, false);
	else if (node->type == HEREDOC)
		type_heredoc(data, node, pipe_struct);
	else
		printf("No Nodetype found\n");
	return (ret);
}
