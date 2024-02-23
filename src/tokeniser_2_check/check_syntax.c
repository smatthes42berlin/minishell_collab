#include "minishell.h"

int	check_syntax(t_list_d *cur_token)
{
	t_list_d	*next_token;
	t_token		*cur_token_val;
	t_token		*next_token_val;

	cur_token_val = cur_token->content;
	next_token = cur_token->next;
	if (next_token)
		next_token_val = next_token->content;
	if (pipe_as_first_token(cur_token, cur_token_val))
		return (token_syntax_error(cur_token_val->value));
	if (operator_as_last_token(next_token, cur_token_val))
		return (token_syntax_error("newline"));
	if (operator_after_operator_execpt_pipe(cur_token_val, next_token_val))
		return (token_syntax_error(next_token_val->value));
	if (two_pipes_in_a_row(cur_token_val, next_token_val))
		return (token_syntax_error(next_token_val->value));
	return (0);
}

int	token_syntax_error(char *token_val)
{
	char	*res;

	(ft_printf_to_str(&res,
			"minishell: syntax error near unexpected token `%s'\n",
			token_val));
	return (throw_error_mimic_bash(res, 127));
}
