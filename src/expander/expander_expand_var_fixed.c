#include "minishell.h"

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
