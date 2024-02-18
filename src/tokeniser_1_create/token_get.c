#include "minishell.h"

int	get_token(t_main_data *main_data, char **cur_pos)
{
	t_token	*new_token;

	new_token = create_token();
	if (!new_token)
		return (1);
	if (append_token_list(main_data, new_token))
	{
		free_token(new_token);
		return (1);
	}
	if (identify_token(cur_pos, new_token))
		return (1);
	return (0);
}
