#include "minishell.h"

static int	free_error_join(char *env_var);

int	expand_variable(t_expansion_info *expansion_info)
{
	bool	found;

	found = false;
	go_to_next_char(expansion_info);
	if (check_for_fixed_expansions(expansion_info, &found))
		return (1);
	if (!found)
	{
		if (check_for_variable_expansions(expansion_info))
			return (2);
	}
	return (0);
}

int	check_for_variable_expansions(t_expansion_info *expansion_info)
{
	char	*key;

	if (!is_valid_var_name_char(*(expansion_info->cur_pos))
		|| ft_isdigit(*(expansion_info->cur_pos)))
		return (go_to_next_char(expansion_info));
	key = get_key_env_var(expansion_info);
	if (!key)
		return (throw_error_custom((t_error_ms){errno, EPART_EXPANDER,
				EFUNC_MALLOC, "duplicating env var key"}));
	if (insert_env_var(expansion_info, NULL, key))
		return (free_char_variadic_code(1, 1, key));
	return (free_char_variadic_code(0, 1, key));
}

int	insert_env_var(t_expansion_info *expansion_info, char *env_var_name,
		char *key)
{
	int		state;
	char	*tmp;
	char	*env_var;
	char	*key_with_dollar;

	if (!env_var_name)
		env_var_name = key;
	env_var = env_get_var(expansion_info->main_data, env_var_name);
	key_with_dollar = ft_strjoin("$", key);
	if (!key_with_dollar)
		return (free_error_join(env_var));
	state = ins_replace_str_after_index(&tmp,
			(t_ins_repl_str){expansion_info->cur_token->value,
			key_with_dollar, env_var, expansion_info->cur_pos_index - 1});
	free(expansion_info->cur_token->value);
	expansion_info->cur_token->value = tmp;
	adjust_cur_pos_str_len(expansion_info, env_var);
	free_char_variadic_code(0, 2, key_with_dollar, env_var);
	if (state)
		return (throw_error_custom((t_error_ms){errno, EPART_EXPANDER,
				EFUNC_MALLOC, "replacing env var in token val $"}));
	return (0);
}

static int	free_error_join(char *env_var)
{
	free(env_var);
	return (throw_error_custom((t_error_ms){errno, EPART_EXPANDER, EFUNC_MALLOC,
			"joining env var key with $"}));
}

char	*get_key_env_var(t_expansion_info *expansion_info)
{
	int		len_var_name;
	int		start_pos_index;
	char	*start_pos;

	len_var_name = 0;
	start_pos_index = expansion_info->cur_pos_index;
	start_pos = expansion_info->cur_pos;
	while (is_valid_var_name_char(*(expansion_info->cur_pos)))
	{
		len_var_name++;
		go_to_next_char(expansion_info);
	}
	expansion_info->cur_pos_index = start_pos_index;
	return (ft_str_n_dup(start_pos, len_var_name + 1));
}
