#include "minishell.h"

int	check_for_fixed_expansions(t_expansion_info *expansion_info, bool *found)
{
	char	*digit;

	if (check_for_specific_fixed_expansion(expansion_info, found, "?",
			"MINISHELL_LAST_EXIT"))
		return (1);
	else if (check_for_specific_fixed_expansion(expansion_info, found, "0",
			"PROGRAM_NAME"))
		return (1);
	else if (ft_isdigit(*(expansion_info->cur_pos)))
	{
		if (ft_str_n_dup_int(expansion_info->cur_pos, 2, &digit) == -1)
			return (throw_error_custom((t_error_ms){errno, EPART_EXPANDER,
					EFUNC_MALLOC, "dup env var first digit"}));
		if (insert_env_var(expansion_info, digit, digit))
			return (1);
		*found = true;
	}
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
