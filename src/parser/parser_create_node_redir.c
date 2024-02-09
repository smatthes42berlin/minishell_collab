
#include "minishell.h"

static int	get_file_name(t_node_redir *redir_node, t_parse_info *parse_info);
static int	init_redir_node_param(t_node_redir *redir_node);
static int	decide_open_mode(t_node_redir *redir_node, t_token *cur_token);
static int	decide_stdin_stdout(t_node_redir *redir_node, t_token *cur_token);

int	create_redir_node(t_parse_info *parse_info)
{
	t_node_redir	*redir_node;
	t_node			*node_generic;

	redir_node = malloc(sizeof(*redir_node));
	if (!redir_node)
		return (printf("Error: Allocating memory for redir node\n"));
	node_generic = (t_node *)redir_node;
	init_generic_node_param(node_generic, REDIR);
	init_redir_node_param(redir_node);
	decide_open_mode(redir_node, parse_info->cur_token);
	decide_stdin_stdout(redir_node, parse_info->cur_token);
	if (get_file_name(redir_node, parse_info))
		return (1);
	if (add_all_but_pipe_ast(parse_info, node_generic))
		return (1);
	set_n_token_as_parsed(2, parse_info);
	print_redir_node(redir_node, true);
	return (0);
}

static int	get_file_name(t_node_redir *redir_node, t_parse_info *parse_info)
{
	t_token	*next_token;

	next_token = parse_info->next->next->content;
	if (ft_str_n_dup_int(next_token->value, 0, &(redir_node->filename)) == -1)
		return printf("Problem duplicating str for redir node filename\n");
	return (0);
}

static int	init_redir_node_param(t_node_redir *redir_node)
{
	redir_node->filename = NULL;
	return (0);
}

static int	decide_open_mode(t_node_redir *redir_node, t_token *cur_token)
{
	if (token_is_redir_out_app(cur_token))
		redir_node->mode = FILE_ONLY_WRITE_APPEND;
	if (token_is_redir_out_trunc(cur_token))
		redir_node->mode = FILE_ONLY_WRITE;
	if (token_is_redir_in(cur_token))
		redir_node->mode = FILE_ONLY_READING;
	return (0);
}

static int	decide_stdin_stdout(t_node_redir *redir_node, t_token *cur_token)
{
	if (token_is_redir_in(cur_token))
		redir_node->in_or_out = STDIN;
	else
		redir_node->in_or_out = STDOUT;
	return (0);
}
