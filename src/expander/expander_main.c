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
		}
		if (remove_empty_token(&next))
			continue ;
		next = next->next;
	}
	debug_expand(main_data);
	return (0);
}
