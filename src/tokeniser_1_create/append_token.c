#include "minishell.h"

int	append_token_list(t_main_data *main_data, t_token *token)
{
	t_list_d	*new_lst_elem;

	new_lst_elem = d_lst_new(token);
	if (!new_lst_elem)
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_MALLOC, "creating new list elem for token"}));
	d_lst_add_back(&main_data->token_list, new_lst_elem);
	return (0);
}
