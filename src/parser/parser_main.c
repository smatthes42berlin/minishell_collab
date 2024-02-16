#include "minishell.h"

static int	identify_token_in_parser(t_parse_info *parse_info,
				int *token_create_success);

int	parse(t_main_data *main_data)
{
	int				token_recognised;
	t_parse_info	parse_info;
	int				token_create_success;

	parse_info.main_data = main_data;
	parse_info.next = main_data->token_list;
	parse_info.root_node_ast = NULL;
	while (parse_info.next)
	{
		parse_info.cur_token = parse_info.next->content;
		token_recognised = identify_token_in_parser(&parse_info,
				&token_create_success);
		if (token_recognised || token_create_success)
			return (1);
	}
	print_ast(parse_info.root_node_ast, 0);
	printf("\n\n\n");
	change_form_of_ast(&parse_info);
	print_ast(parse_info.ast_rene, 0);
	main_data->ast = parse_info.ast_rene;
	return (0);
}

static int	identify_token_in_parser(t_parse_info *parse_info,
									int *token_create_success)
{
	*token_create_success = 0;
	if (parse_info->cur_token->parsed)
		got_to_nth_next_token(1, parse_info);
	else if (token_is_redir(parse_info->cur_token))
		*token_create_success = create_redir_node(parse_info);
	else if (token_is_here_doc(parse_info->cur_token))
		*token_create_success = create_hdoc_node(parse_info);
	else if (token_is_pipe(parse_info->cur_token))
		*token_create_success = create_pipe_node(parse_info);
	else if (token_is_word(parse_info->cur_token))
		*token_create_success = create_exec_node(parse_info);
	else
		return (throw_error_custom((t_error_ms){127, EPART_PARSER,
				EFUNC_DEV_ISSUE, "token type not recognised"}));
	return (0);
}
