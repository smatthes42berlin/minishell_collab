#include "minishell.h"

int	expand(t_main_data *main_data)
{
	t_list_d	*next;
	t_token		*cur_token;

	next = main_data->token_list;
	while (next)
	{
		cur_token = next->content;
		if (!token_is_operator_token(cur_token))
		{
			if (check_expansion(cur_token, main_data))
				return (1);
			// remove_quotes(&next, cur_token);
		}
		next = next->next;
	}
	return (0);
}

int	check_expansion(t_token *token, t_main_data *main_data)
{
	t_expansion_info	expansion_info;

	expansion_info.main_data = main_data;
	expansion_info.cur_token = token;
	expansion_info.inside_dquotes = false;
	expansion_info.cur_pos = token->value;
	expansion_info.cur_pos_index = 0;
	while (*(expansion_info.cur_pos))
	{
		if (expand_token_val(&expansion_info))
			return (1);
	}
	return (0);
}

int	expand_token_val(t_expansion_info *expansion_info)
{
	if (is_squote(*(expansion_info->cur_pos))
		&& !expansion_info->inside_dquotes)
		return (skip_to_closing_quote(expansion_info));
	if (check_dquote_start_end(expansion_info))
		return (0);
	if (is_dollar_char(*(expansion_info->cur_pos)))
		return (expand_variable(expansion_info));
	return (go_to_next_char(expansion_info));
}

int	check_dquote_start_end(t_expansion_info *expansion_info)
{
	if (is_dquote(*(expansion_info->cur_pos))
		&& !expansion_info->inside_dquotes)
	{
		expansion_info->inside_dquotes = true;
		remove_quote(expansion_info->cur_pos);
		return (1);
	}
	if (is_dquote(*(expansion_info->cur_pos)) && expansion_info->inside_dquotes)
	{
		expansion_info->inside_dquotes = false;
		remove_quote(expansion_info->cur_pos);
		return (1);
	}
	return (0);
}

int	remove_quote(char *cur_pos)
{
	int	i;
	int	str_len;

	i = 1;
	str_len = ft_strlen(cur_pos);
	while (i < str_len)
	{
		cur_pos[i - 1] = cur_pos[i];
		i++;
	}
	cur_pos[i - 1] = '\0';
	return (0);
}
