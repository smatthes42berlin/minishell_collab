#include "minishell.h"

int	identify_token(char **cur_pos, t_token *token)
{
	if (is_operator(**cur_pos))
		return (create_operator_token(cur_pos, token));
	else
		return (create_word_token(cur_pos, token));
}

int	create_word_token(char **cur_pos, t_token *token)
{
	char	*token_val;
	int		num_characters;

	num_characters = count_characters(*cur_pos);
	if (num_characters == -1)
		return (printf("ERROR: no closing quote found"));
	if (ft_str_n_dup_int(*cur_pos, num_characters + 1, &token_val) == -1)
		return (printf("Error: duplicating string for token\n"));
	token->type = T_WORD;
	token->value = token_val;
	*cur_pos = *cur_pos + num_characters;
	return (0);
}

int	create_operator_token(char **cur_pos, t_token *token)
{
	if (identify_operator(cur_pos, token))
		return (printf("ERROR: Identifying Token Type!"));
	if (token->type == T_UNDEFINED)
		return (printf("ERROR: Operator not handled!"));
	return (0);
}
