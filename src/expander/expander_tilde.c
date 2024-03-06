#include "minishell.h"

static int	replace_tilde_path(t_token *cur_token, t_main_data *main_data);

int	expander_tilde(t_token *cur_token, t_main_data *main_data)
{
	if (ft_strcmp("~", cur_token->value) == 0)
	{
		free(cur_token->value);
		cur_token->value = env_get_var(main_data, "HOME");
		if (!cur_token->value)
			return (1);
	}
	if (ft_strncmp("~/", cur_token->value, 2) == 0)
	{
		if (replace_tilde_path(cur_token, main_data))
			return (1);
	}
	return (0);
}

static int	replace_tilde_path(t_token *cur_token, t_main_data *main_data)
{
	char	*tmp;
	char	*home;
	int		state;

	home = env_get_var(main_data, "HOME");
	if (!cur_token->value)
		return (1);
	state = ins_replace_str_after_index(&tmp, (t_ins_repl_str){cur_token->value,
			"~", home, 0});
	free_char_variadic_code(0, 2, cur_token->value, home);
	cur_token->value = tmp;
	if (state)
		return (throw_error_custom((t_error_ms){errno, EPART_EXPANDER,
				EFUNC_MALLOC,
				"replacing env var in token val in tilde expansion"}));
	return (0);
}
