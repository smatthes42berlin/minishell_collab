#include "./lib_main.h"

char	**ft_arr_char_add_replace_n(char **arr, char *val)
{
	char	**removed;
	char	**new;

	removed = ft_arr_char_rem_n(arr, val);
	if (!removed)
		return (NULL);
	new = ft_arr_char_add(removed, val);
	free_str_arr_null(removed);
	if (!new)
		return (NULL);
	return (new);
}
