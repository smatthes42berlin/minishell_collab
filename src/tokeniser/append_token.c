#include "minishell.h"

int	append_token_list(t_main_data *main_data, t_token *token)
{
	t_list_dc	*new_lst_elem;

	new_lst_elem = dc_lst_new(token);
	if (!new_lst_elem)
		return (printf("Error: creating new list elem for token"));
	dc_lst_add_back(&main_data->token_list, new_lst_elem);
	return (0);
}
