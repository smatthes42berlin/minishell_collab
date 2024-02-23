#include "minishell.h"

t_token	*create_token()
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
			EFUNC_MALLOC, "create token"});
		return (NULL);
	}
	token->type = T_UNDEFINED;
	token->value = NULL;
	token->parsed = false;
	return (token);
}
