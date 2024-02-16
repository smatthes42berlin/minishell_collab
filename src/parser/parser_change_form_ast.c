#include "minishell.h"

static bool	is_not_last_pipe(t_node *node);
static bool	first_node_no_pipe(t_parse_info *parse_info);
static bool	only_one_pipe(t_parse_info *parse_info);

int	change_form_of_ast(t_parse_info *parse_info)
{
	t_node	*cur_pipe;

	parse_info->ast_steffen = parse_info->root_node_ast;
	parse_info->ast_rene = parse_info->root_node_ast;
	if (first_node_no_pipe(parse_info) || only_one_pipe(parse_info))
		return (0);
	parse_info->ast_rene->parent_node = parse_info->ast_rene->left_node;
	parse_info->ast_rene->left_node = 
		parse_info->ast_rene->parent_node->right_node;
	cur_pipe = parse_info->ast_rene->parent_node;
	while (cur_pipe)
	{
		parse_info->ast_rene = cur_pipe;
		cur_pipe->right_node = cur_pipe->parent_node;
		if (is_not_last_pipe(cur_pipe))
		{
			cur_pipe->parent_node = cur_pipe->left_node;
			cur_pipe->left_node = cur_pipe->left_node->right_node;
		}
		else
			cur_pipe->parent_node = NULL;
		cur_pipe = cur_pipe->parent_node;
	}
	return (0);
}

static bool	is_not_last_pipe(t_node *node)
{
	return (node_is_pipe(node->left_node));
}

static bool	first_node_no_pipe(t_parse_info *parse_info)
{
	return (!node_is_pipe(parse_info->root_node_ast));
}

static bool	only_one_pipe(t_parse_info *parse_info)
{
	return (!node_is_pipe(parse_info->root_node_ast->left_node));
}
