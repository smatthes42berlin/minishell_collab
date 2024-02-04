#include "minishell.h"

int	expand(t_main_data *main_data)
{
	t_list_d	*next;

	next = main_data->token_list;
	while (next)
	{
		if (check_expansion(next->content, main_data))
			return (1);
		next = next->next;
	}
	// if (check_expansion(next->content, main_data))
	// 	return (1);
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
	if (token_is_operator_token(expansion_info.cur_token))
		return (0);
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
		(skip_to_closing_quote(expansion_info));
	check_dquote_start_end(expansion_info);
	if (is_dollar_char(*(expansion_info->cur_pos)))
	{
		return (expand_variable(expansion_info));
	}
	return (go_to_next_char(expansion_info));
}

int	check_dquote_start_end(t_expansion_info *expansion_info)
{
	if (is_dquote(*(expansion_info->cur_pos))
		&& !expansion_info->inside_dquotes)
	{
		expansion_info->inside_dquotes = true;
		go_to_next_char(expansion_info);
	}
	if (is_dquote(*(expansion_info->cur_pos)) && expansion_info->inside_dquotes)
	{
		expansion_info->inside_dquotes = false;
		go_to_next_char(expansion_info);
	}
	return (0);
}
