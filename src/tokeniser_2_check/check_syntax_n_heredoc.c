#include "minishell.h"

// two operators after each other -> syntax error
// last token operator -> syntax error newline
// created new token list checked and with heredoc expanded
int	check_syntax_n_heredoc(t_main_data *main_data)
{
	t_list_d *cur_token;

	cur_token = main_data->token_list;
	printf("checking \n\n%s\n\n", main_data->cli_input);
	while (cur_token->next)
	{
		printf("1\n");
		cur_token = cur_token->next;
	}
	printf("1\n");
	return (1);
}