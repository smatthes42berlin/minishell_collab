#include "lib_main.h"

// n must contain space for null byte
int	ft_str_n_join_int(char const *s1, char const *s2, int n, char **res)
{
	size_t	str_len_1;
	size_t	str_len_2;

	*res = NULL;
	if (!s1 && !s2)
		return (1);
	if (!s1)
		return (ft_str_n_dup_int(s2, n, res));
	if (!s2)
		return (ft_str_n_dup_int(s1, n, res));
	str_len_2 = ft_strlen(s2);
	str_len_1 = ft_strlen(s1);
	if (n == 0)
		n = str_len_2 + 1;
	*res = malloc(sizeof(**res) * (str_len_1 + n));
	if (!(*res))
		return (-1);
	ft_strlcpy(*res, s1, str_len_1 + 1);
	ft_strlcpy(*res + str_len_1, s2, n);
	return (1);
}
