#include "minishell.h"

int	skip_to_closing_quote(t_expansion_info *expansion_info)
{
	int	index_closing_quote;

	remove_quote(expansion_info->cur_pos);
	index_closing_quote = has_closing_quote(expansion_info->cur_pos, '\'');
	remove_quote(expansion_info->cur_pos + index_closing_quote);
	expansion_info->cur_pos = expansion_info->cur_pos + index_closing_quote;
	expansion_info->cur_pos_index = expansion_info->cur_pos_index
		+ index_closing_quote;
	return (0);
}

int	go_to_next_char(t_expansion_info *expansion_info)
{
	(expansion_info->cur_pos)++;
	expansion_info->cur_pos_index++;
	return (0);
}

int	adjust_cur_pos_num(t_expansion_info *expansion_info, int num_add)
{
	expansion_info->cur_pos_index = expansion_info->cur_pos_index + num_add;
	expansion_info->cur_pos = &((expansion_info->cur_token->value
				)[expansion_info->cur_pos_index]);
	return (0);
}

int	adjust_cur_pos_str_len(t_expansion_info *expansion_info, char *insert_str)
{
	int	str_len;

	str_len = ft_strlen(insert_str);
	return (adjust_cur_pos_num(expansion_info, str_len - 1));
}
