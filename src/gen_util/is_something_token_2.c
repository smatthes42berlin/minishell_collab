#include "minishell.h"

bool	token_is_pipe(t_token *token)
{
	return (token->type == T_PIPE);
}

bool	token_is_redir_in(t_token *token)
{
	return (token->type == T_LESS);
}

bool	token_is_redir_out_trunc(t_token *token)
{
	return (token->type == T_GREAT);
}

bool	token_is_redir_out_app(t_token *token)
{
	return (token->type == T_DGREAT);
}

bool	token_is_here_doc(t_token *token)
{
	return (token->type == T_HEREDOC);
}
