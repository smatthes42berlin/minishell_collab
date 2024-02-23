#include "minishell.h"

void	print_type(t_node *node)
{
	if (node->type == EXEC)
		printf("EXEC\n");
	if (node->type == PIPE)
		printf("PIPE\n");
	if (node->type == REDIR)
		printf("REDIR\n");
	if (node->type == HEREDOC)
		printf("HEREDOC\n");
}
