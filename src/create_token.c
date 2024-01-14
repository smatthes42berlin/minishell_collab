#include "minishell.h"

int	creat_dquote_token(char **cur_pos, t_main_data *main_data)
{
	int			closing_quote;
	char		*new_token;
	t_list_dc	*new_lst_elem;

	(*cur_pos)++;
	printf("creating token");
	closing_quote = has_closing_quote(*cur_pos, '"');
	if (closing_quote == -1)
	{
		
	}
		return (printf("Error: no closing quote"));
	if (ft_str_n_dup_int(*cur_pos, closing_quote, &new_token) == -1)
		return (printf("Error: duplicating string for token"));
	new_lst_elem = dc_lst_new(new_token);
	if (!new_lst_elem)
		return (printf("Error: creating new list elem for token"));
	dc_lst_add_back(&main_data->token_list, new_lst_elem);
	*cur_pos = *cur_pos + closing_quote + 1;
	return (0);
}
