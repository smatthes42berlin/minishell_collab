#include "minishell.h"

static int	print_sep_debug(void);

int	debug_tokenise(t_main_data *main_data)
{
	if (PRINT_DEBUG_1)
	{
		printf("Token list after tokenisation\n");
		print_token_list(main_data->token_list);
		print_sep_debug();
	}
	return (0);
}

int	debug_expand(t_main_data *main_data)
{
	if (PRINT_DEBUG_1)
	{
		printf("Token list after expansion\n");
		print_token_list(main_data->token_list);
		print_sep_debug();
	}
	return (0);
}

int	debug_parse(t_main_data *main_data)
{
	if (PRINT_DEBUG_1)
	{
		printf("AST after parsing\n");
		print_all_nodes_ast(main_data->ast);
		print_ast(main_data->ast, 0);
		print_sep_debug();
	}
	return (0);
}

int	print_all_nodes_ast(t_node *node)
{
	if (!node)
		return (0);
	print_node_ast(node);
	print_all_nodes_ast(node->left_node);
	print_all_nodes_ast(node->right_node);
	return (0);
}

static int	print_sep_debug(void)
{
	printf("\n***************************************************\n");
	return (0);
}
