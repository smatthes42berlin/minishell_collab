#include "minishell.h"

static int	print_according_node(t_node *nood, int depth);

void	print_ast(t_node *root, int depth)
{
	char	*sep;
	int		i;

	i = 0;
	sep = "-----------";
	if (!root)
		return ;
	// if (depth == 10)
	// {
	// 	printf("Aborted printing\n");
	// 	return ;
	// }
	print_ast(root->right_node, depth + 1);
	printf("%s\n", sep);
	while (i < depth)
	{
		printf("%s", sep);
		i++;
	}
	print_according_node(root, depth);
	// printf("%d:\"%d\"\n", depth, root->type);
	print_ast(root->left_node, depth + 1);
}

static int	print_according_node(t_node *node, int depth)
{
	printf("%d: ", depth);
	if (node_is_pipe(node))
		print_pipe_node((t_node_pipe *)node, 0);
	else if (node_is_hdoc(node))
		print_hdoc_node((t_node_heredoc *)node, 0);
	else if (node_is_redir(node))
		print_redir_node((t_node_redir *)node, 0);
	else if (node_is_exec(node))
		print_exec_node((t_node_exec *)node, 0);
	else
		return (0);
	return (0);
}