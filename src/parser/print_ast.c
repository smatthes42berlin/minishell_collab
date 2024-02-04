#include "minishell.h"

void	print_ast(t_node *root, int depth)
{
	char	*sep;
	int		i;

	i = 0;
	sep = "-----------";
	
	if (!root)
		return ;
	if (depth == 5)
	{
		printf("Aborted printing\n");
		return ;
	}
	print_ast(root->right_node, depth + 1);
	printf("%s\n", sep);
	while (i < depth)
	{
		printf("%s", sep);
		i++;
	}
	printf("%d:\"%s\"\n", depth, root->token_value);
	print_ast(root->left_node, depth + 1);
}
