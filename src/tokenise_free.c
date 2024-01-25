#include "minishell.h"

void	free_token(void *token)
{
	t_token *token_cast;

	token_cast = token;
	free(token_cast->value);
}