#include "minishell.h"

void	print_token_list(t_list_d *token_list)
{
	t_list_d	*next;
	// t_token		*token_test;

	if (!token_list)
		return ;
	printf("\n\n********TOKEN_LIST\n\n");
	next = token_list;
	printf("Oo\n");
	// token_test = next->next->content;
	// printf("$%s$\n", token_test->value);
	while (next->next)
	{
		printf("Aa\n");
		print_token(next->content);
		printf("Cc\n");
		next = next->next;
	}
	print_token(next->content);
	return ;
}

void	print_token(t_token *token)
{
	printf("********\n");
	printf("token type = $%d$\n", token->type);
	printf("token value = $%s$\n", token->value);
	printf("********\n\n");
}
