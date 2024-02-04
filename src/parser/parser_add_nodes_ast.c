
#include "minishell.h"

int	add_all_but_pipe_ast(t_parse_info *parse_info, t_node *new_node)
{
	if (check_new_root_node(parse_info, new_node))
		return (0);
	append_to_last_redir(parse_info->root_node_ast, new_node);
	return (0);
}

int	add_pipe_ast(t_parse_info *parse_info, t_node_pipe *new_node)
{
	t_node	*new_node_gen;

	new_node_gen = (t_node *)new_node;
	if (check_new_root_node(parse_info, new_node_gen))
		return (0);
	parse_info->root_node_ast->parent_node = new_node_gen;
	new_node->left_node = parse_info->root_node_ast;
	parse_info->root_node_ast = new_node_gen;
	return (0);
}
