#include "lib_main.h"

static int	dup_org_str(char *org_str, char **res);

int	rem_str_after_index(char **res, t_ins_repl_str replace_info)
{
	char	**splitted_str;
	int		join_state;
	char	*tmp;

	*res = NULL;
	if (!replace_info.org_str)
		return (1);
	if (str_contains_str_index(replace_info.org_str
			+ replace_info.search_start_index, replace_info.repl_str) == -1)
		return (dup_org_str(replace_info.org_str, res));
	if (split_str_str_after_index(replace_info.org_str, replace_info.repl_str,
			&splitted_str, replace_info.search_start_index))
		return (3);
	join_state = ft_join_n_str(&tmp, 2, splitted_str[0], splitted_str[1]);
	free_str_arr(splitted_str, 2);
	if (join_state == -1)
		return (4);
	*res = tmp;
	return (0);
}

static int	dup_org_str(char *org_str, char **res)
{
	if (ft_str_n_dup_int(org_str, 0, res) == -1)
		return (2);
	return (0);
}
