#include "minishell.h"

bool	token_is_operator_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == T_DLESS || token->type == T_DGREAT
		|| token->type == T_LESS || token->type == T_GREAT
		|| token->type == T_PIPE);
}

bool	token_is_redir(t_token *token)
{
	return (token_is_redir_in(token) || token_is_redir_out_app(token)
		|| token_is_redir_out_trunc(token));
}

bool	token_is_word(t_token *token)
{
	return (token->type == T_WORD);
}
