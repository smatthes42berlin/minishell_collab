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
	if (!(cur_token->prev) && cur_token_val->type == T_PIPE)
	{
		printf("\n1\n");
		return (token_syntax_error(cur_token_val->value));
	}
	if (token_is_operator(cur_token_val) && !next_token)
	{
		printf("\n2\n");
		return (token_syntax_error("newline"));
	}
	if (token_is_operator(cur_token_val) && token_is_operator(next_token_val))
	{
		printf("\n3\n");
		return (token_syntax_error(next_token_val->value));
	}
	return (0);
}

int	token_is_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == T_DLESS || token->type == T_DGREAT
		|| token->type == T_LESS || token->type == T_GREAT
		|| token->type == T_PIPE);
}

int	token_syntax_error(char *token_val)
{
	(printf("minishell: syntax error near unexpected token `%s'\n", token_val));
	return (1);
}