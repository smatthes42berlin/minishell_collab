#include "minishell.h"


int	remove_here_doc_token(t_main_data *main_data)
{
	t_list_d	*cur_token;
	t_token		*cur_token_val;
	t_list_d	*tmp;

	cur_token = main_data->token_list;
	while (cur_token && cur_token->next)
	{
		cur_token_val = cur_token->content;
		if (cur_token_val->type == T_DLESS)
		{
			if (!cur_token->prev)
				main_data->token_list = cur_token->next;
			tmp = d_lst_pop_current(&cur_token);
			d_lst_del_one(tmp, free_token);
		}
		else
			cur_token = cur_token->next;
	}
	return (0);
}
