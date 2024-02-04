
#include "minishell.h"

int	init_generic_node_param(t_node *node, enum e_node_type type, char *value)
{
	node->type = type;
	node->parent_node = NULL;
	node->left_node = NULL;
	node->right_node = NULL;
	node->token_value = value;
	return (0);
}

int	create_redir_node(t_parse_info *parse_info)
{
	t_node_redir	*redir_node;
	t_node			*node_generic;

	redir_node = malloc(sizeof(*redir_node));
	if (!redir_node)
		return (printf("Error: Allocating memory for redir node\n"));
	node_generic = (t_node *)redir_node;
	init_generic_node_param(node_generic, REDIR, parse_info->cur_token->value);
	if (add_all_but_pipe_ast(parse_info, node_generic))
		return (1);
	set_n_token_as_parsed(2, parse_info);
	return (0);
}

int	create_hdoc_node(t_parse_info *parse_info)
{
	t_node_heredoc	*hdoc_node;
	t_node			*node_generic;

	hdoc_node = malloc(sizeof(t_node_heredoc));
	if (!hdoc_node)
		return (printf("Error: Allocating memory for hdocnode \n"));
	node_generic = (t_node *)hdoc_node;
	init_generic_node_param(node_generic, HEREDOC,
			parse_info->cur_token->value);
	if (add_all_but_pipe_ast(parse_info, node_generic))
		return (1);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}

int	create_exec_node(t_parse_info *parse_info)
{
	t_node_exec	*exec_node;
	t_node		*node_generic;

	exec_node = malloc(sizeof(t_node_exec));
	if (!exec_node)
		return (printf("Error: Allocating memory for exec node \n"));
	node_generic = (t_node *)exec_node;
	init_generic_node_param(node_generic, EXEC, parse_info->cur_token->value);
	if (add_all_but_pipe_ast(parse_info, node_generic))
		return (1);
	printf("11!\n\n");
	set_exec_args_as_parsed(parse_info);
	printf("22!\n\n");
	return (0);
}

int	create_pipe_node(t_parse_info *parse_info)
{
	t_node_pipe	*pipe_node;
	t_node		*node_generic;

	pipe_node = malloc(sizeof(t_node_pipe));
	if (!pipe_node)
		return (printf("Error: Allocating memory for pipe node\n"));
	node_generic = (t_node *)pipe_node;
	init_generic_node_param(node_generic, PIPE, parse_info->cur_token->value);
	if (add_pipe_ast(parse_info, pipe_node))
		return (1);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}
