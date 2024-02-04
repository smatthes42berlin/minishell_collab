#include "lib_main.h"

static int	dup_org_str(char *org_str, char **res);

int	ins_replace_str(char *org_str, char **res, char *repl_str, char *ins_str)
{
	char	**splitted_str;
	int		join_state;
	char	*tmp;

	*res = NULL;
	if (!org_str || !repl_str)
		return (1);
	if (str_contains_str_index(org_str, repl_str) == -1)
		return (dup_org_str(org_str, res));
	if (split_str_str_first_occ(org_str, repl_str, &splitted_str))
		return (3);
	join_state = ft_join_n_str(&tmp, 3, splitted_str[0], ins_str,
			splitted_str[1]);
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
