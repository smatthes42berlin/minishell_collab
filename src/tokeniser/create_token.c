#include "minishell.h"


t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = UNDEFINED;
	token->value = NULL;
	return (token);
}

