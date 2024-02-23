#include "minishell.h"

static char	*get_token_type_name(enum e_token_type token_type);

void	print_token_list(t_list_d *token_list)
{
	t_list_d	*next;

	if (!token_list)
		return ;
	printf("\n\n********TOKEN_LIST\n\n");
	next = token_list;
	while (next->next)
	{
		print_token(next->content);
		next = next->next;
	}
	print_token(next->content);
	return ;
}

void	print_token(t_token *token)
{
	printf("********\n");
	printf("token type = $%s$\n", get_token_type_name(token->type));
	printf("token value = $%s$\n", token->value);
	printf("********\n\n");
}

static char	*get_token_type_name(enum e_token_type token_type)
{
	if (token_type == T_WORD)
		return ("WORD");
	if (token_type == T_DLESS)
		return ("DLESS");
	if (token_type == T_DGREAT)
		return ("DGREAT");
	if (token_type == T_LESS)
		return ("LESS");
	if (token_type == T_GREAT)
		return ("GREAT");
	if (token_type == T_PIPE)
		return ("PIPE");
	if (token_type == T_HEREDOC)
		return ("HEREDOC");
	if (token_type == T_UNDEFINED)
		return ("UNDEFINED");
	return (NULL);
}
