#include "minishell.h"

void	print_token_list(t_list_d *token_list)
{
	t_list_d	*head;
	t_list_d	*next;

	head = token_list;
	if (!token_list)
		return ;
	printf("\n\n********TOKEN_LIST\n\n");
	print_token(head->content);
	next = head->next;
	while (next != head)
	{
		print_token(next->content);
		next = next->next;
	}
	return ;
}

void	print_token(t_token *token)
{
	printf("********\n");
	printf("token type = %d\n", token->type);
	printf("token value = %s\n", token->value);
	printf("********\n\n");
}

