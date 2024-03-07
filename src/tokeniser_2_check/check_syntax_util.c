#include "minishell.h"

int	pipe_as_first_token(t_list_d *cur_token, t_token *cur_token_val)
{
	return (!(cur_token->prev) && cur_token_val->type == T_PIPE);
}

int	operator_as_last_token(t_list_d *next_token, t_token *cur_token_val)
{
	return (token_is_operator_token(cur_token_val) && !next_token);
}

int	two_pipes_in_a_row(t_token *cur_token_val,
						t_token *next_token_val)
{
	return (cur_token_val->type == T_PIPE && next_token_val->type == T_PIPE);
}

int	operator_after_operator_execpt_pipe(
	t_token *cur_token_val, t_token *next_token_val)
{
	return (!token_is_pipe(cur_token_val)
		&& token_is_operator_token(cur_token_val)
		&& token_is_operator_token(next_token_val));
}
