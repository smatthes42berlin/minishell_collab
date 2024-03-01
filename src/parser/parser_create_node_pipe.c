#include "minishell.h"

int	create_pipe_node(t_parse_info *parse_info)
{
	t_node_pipe	*pipe_node;
	t_node		*node_generic;

	pipe_node = malloc(sizeof(t_node_pipe));
	if (!pipe_node)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "pipe node"}));
	node_generic = (t_node *)pipe_node;
	init_generic_node_param(node_generic, PIPE);
	add_pipe_ast(parse_info, pipe_node);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}
