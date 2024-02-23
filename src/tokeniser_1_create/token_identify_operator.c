#include "minishell.h"

static int	assign_token_type(enum e_token_type token_type,
				char *token_value,
				t_token *token);
static int	ret_incre_one(enum e_token_type token_type,
				char *token_value,
				char **cur_pos,
				t_token *token);

static int	ret_incre_two(enum e_token_type token_type,
				char *token_value,
				char **cur_pos,
				t_token *token);

int	identify_operator(char **cur_pos, t_token *token)
{
	if ((*cur_pos)[0] == '<')
	{
		if ((*cur_pos)[1] == '<')
			return (ret_incre_two(T_DLESS, "<<", cur_pos, token));
		return (ret_incre_one(T_LESS, "<", cur_pos, token));
	}
	if ((*cur_pos)[0] == '>')
	{
		if ((*cur_pos)[1] == '>')
			return (ret_incre_two(T_DGREAT, ">>", cur_pos, token));
		return (ret_incre_one(T_GREAT, ">", cur_pos, token));
	}
	if ((*cur_pos)[0] == '|')
		return (ret_incre_one(T_PIPE, "|", cur_pos, token));
	return (ret_incre_one(T_UNDEFINED, NULL, cur_pos, token));
}

static int	assign_token_type(enum e_token_type token_type,
								char *token_value,
								t_token *token)
{
	token->type = token_type;
	token->value = ft_str_n_dup(token_value, 0);
	if (!token->value)
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_MALLOC, "assign token type"}));
	return (0);
}

static int	ret_incre_one(enum e_token_type token_type,
							char *token_value,
							char **cur_pos,
							t_token *token)
{
	if (assign_token_type(token_type, token_value, token))
		return (1);
	(*cur_pos)++;
	return (0);
}

static int	ret_incre_two(enum e_token_type token_type,
							char *token_value,
							char **cur_pos,
							t_token *token)
{
	if (assign_token_type(token_type, token_value, token))
		return (1);
	(*cur_pos) = (*cur_pos) + 2;
	return (0);
}
