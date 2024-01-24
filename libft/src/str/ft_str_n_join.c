#include "lib_main.h"

// n must contain space for null byte
char	*ft_str_n_join(char const *s1, char const *s2, int n)
{
	size_t	str_len_1;
	size_t	str_len_2;
	char	*res_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_str_n_dup(s2, n));
	if (!s2)
		return (ft_str_n_dup(s1, n));
	str_len_2 = ft_strlen(s2);
	str_len_1 = ft_strlen(s1);
	if (n == 0)
		n = str_len_2 + 1;
	res_str = malloc(sizeof(*res_str) * (str_len_1 + n));
	if (!res_str)
		return (NULL);
	ft_strlcpy(res_str, s1, str_len_1 + 1);
	ft_strlcpy(res_str + str_len_1, s2, n);
	return (res_str);
}
