#include "minishell.h"

int	expander_tilde(t_token *cur_token, t_main_data *main_data)
{
	if (ft_strcmp("~", cur_token->value) == 0)
	{
		free(cur_token->value);
		cur_token->value = env_get_var(main_data, "HOME");
		if (!cur_token->value)
			return (1);
	}
	return (0);
}
