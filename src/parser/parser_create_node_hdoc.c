#include "minishell.h"

static int	write_token_value_to_pipe(t_parse_info *parse_info,
										t_node_heredoc *hdoc_node);
static int	init_hdoc_node_param(t_node_heredoc *hdoc_node);

int	create_hdoc_node(t_parse_info *parse_info)
{
	t_node_heredoc	*hdoc_node;
	t_node			*node_generic;

	hdoc_node = malloc(sizeof(t_node_heredoc));
	if (!hdoc_node)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "hdocnode node"}));
	node_generic = (t_node *)hdoc_node;
	init_hdoc_node_param(hdoc_node);
	init_generic_node_param(node_generic, HEREDOC);
	if (write_token_value_to_pipe(parse_info, hdoc_node))
		free_node_creation_code(node_generic, 1);
	add_all_but_pipe_ast(parse_info, node_generic);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}

static int	init_hdoc_node_param(t_node_heredoc *hdoc_node)
{
	hdoc_node->read_fd = -1;
	return (0);
}

static int	write_token_value_to_pipe(t_parse_info *parse_info,
										t_node_heredoc *hdoc_node)
{
	int	fd[2];
	int	write_len;

	if (pipe(fd))
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER, EFUNC_PIPE,
				"hdocnode node opening pipe"}));
	write_len = ft_strlen(parse_info->cur_token->value);
	if (write(fd[1], parse_info->cur_token->value, write_len) == -1)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER, EFUNC_PIPE,
				"hdocnode node writing to pipe"}));
	if (close(fd[1]))
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_CLOSE, "hdocnode node closing write end of pipe"}));
	hdoc_node->read_fd = fd[0];
	return (0);
}
