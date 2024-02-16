#include "minishell.h"

// problem, wihtout quotes gets not expanded
// problem, what if env var has also quotes in it

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
		return (printf("Error: duplicating env var key\n"));
	if (insert_env_var(expansion_info, NULL, key))
		return (free_char_variadic_code(1, 1, key));
	return (free_char_variadic_code(0, 1, key));
}

int	insert_env_var(t_expansion_info *expansion_info, char *env_var_name,
		char *key)
{
	int		replace_state;
	char	*tmp;
	char	*env_var;
	char	*key_with_dollar;

	if (!env_var_name)
		env_var_name = key;
	env_var = env_get_var(expansion_info->main_data, env_var_name);
	key_with_dollar = ft_strjoin("$", key);
	if (!key_with_dollar)
		return (free_char_variadic_msg("Error: joining env var key with $", 1,
				env_var));
	replace_state = ins_replace_str_after_index(&tmp,
			(t_ins_repl_str){expansion_info->cur_token->value, key_with_dollar,
			env_var, expansion_info->cur_pos_index - 1});
	free(expansion_info->cur_token->value);
	expansion_info->cur_token->value = tmp;
	adjust_cur_pos_str_len(expansion_info, env_var);
	free_char_variadic_code(0, 2, key_with_dollar, env_var);
	if (replace_state)
		return (printf("Error: replacing env var in token val $\n"));
	return (0);
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

int	check_for_fixed_expansions(t_expansion_info *expansion_info, bool *found)
{
	if (check_for_specific_fixed_expansion(expansion_info, found, "?",
			"MINISHELL_LAST_EXIT"))
		return (1);
	return (0);
}

int	check_for_specific_fixed_expansion(t_expansion_info *expansion_info,
										bool *found,
										char *spec_var_symbol,
										char *spec_var_name)
{
	int	var_symbol_len;

	var_symbol_len = ft_strlen(spec_var_symbol);
	if (ft_strncmp(expansion_info->cur_pos, spec_var_symbol,
			var_symbol_len) == 0)
	{
		if (insert_env_var(expansion_info, spec_var_name, spec_var_symbol))
			return (1);
		*found = true;
	}
	return (0);
}
