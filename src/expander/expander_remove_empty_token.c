#include "minishell.h"

int	remove_empty_token(t_list_d **next, t_main_data *main_data)
{
	t_token		*cur_token;
	t_list_d	*empty;

	cur_token = (*next)->content;
	if (!token_is_word(cur_token))
		return (0);
	if (str_is_empty(cur_token->value))
	{
		if (d_lst_is_first(*next))
			main_data->token_list = (*next)->next;
		empty = d_lst_pop_current(next);
		d_lst_del_one(empty, free_token);
		return (1);
	}
	return (0);
}
