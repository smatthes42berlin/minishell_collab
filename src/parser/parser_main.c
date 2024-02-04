
#include "minishell.h"

// check token type
// word -> create exec node get all next words as arguments
// operator -> create pipe or redirect node
// heredoc -> create heredoc node, write content to pipe and get pipe fd
//

int	parse(t_main_data *main_data)
{
	int				create_sucess;
	t_parse_info	parse_info;

	parse_info.next = main_data->token_list;
	parse_info.root_node_ast = NULL;
	while (parse_info.next)
	{
		create_sucess = false;
		parse_info.cur_token = parse_info.next->content;
		printf("KK: %s \n\n", parse_info.cur_token->value);
		if (parse_info.cur_token->parsed)
		{
			printf("PP: %s \n\n", parse_info.cur_token->value);
			got_to_nth_next_token(1, &parse_info);
			create_sucess = 0;
		}
		else if (token_is_redir(parse_info.cur_token))
			create_sucess = create_redir_node(&parse_info);
		else if (token_is_here_doc(parse_info.cur_token))
			create_sucess = create_hdoc_node(&parse_info);
		else if (token_is_pipe(parse_info.cur_token))
			create_sucess = create_pipe_node(&parse_info);
		else if (token_is_word(parse_info.cur_token))
			create_sucess = create_exec_node(&parse_info);
		else
			return (printf("Error: token type not recognised during parsing"));
		if (create_sucess)
		{
			// here function to free current ast needed
			return (1);
		}
	}
	printf("hey ho : %s\n\n", parse_info.root_node_ast->token_value);
	printf("hey ho : %s\n\n",
			parse_info.root_node_ast->left_node->token_value);
	print_ast(parse_info.root_node_ast, 0);
	return (0);
}
