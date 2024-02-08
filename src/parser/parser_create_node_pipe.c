
#include "minishell.h"

int	create_pipe_node(t_parse_info *parse_info)
{
	t_node_pipe	*pipe_node;
	t_node		*node_generic;

	pipe_node = malloc(sizeof(t_node_pipe));
	if (!pipe_node)
		return (printf("Error: Allocating memory for pipe node\n"));
	node_generic = (t_node *)pipe_node;
	init_generic_node_param(node_generic, PIPE);
	if (add_pipe_ast(parse_info, pipe_node))
		return (1);
	set_n_token_as_parsed(1, parse_info);
	// print_pipe_node(pipe_node, true);
	return (0);
}
