#include "lib_main.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str_len_1;
	size_t	str_len_2;
	char	*res_str;

	str_len_1 = ft_strlen(s1);
	str_len_2 = ft_strlen(s2);
	res_str = malloc(sizeof(*res_str) * (str_len_1 + str_len_2 + 1));
	if (!res_str)
		return (NULL);
	ft_strlcpy(res_str, s1, str_len_1 + 1);
	ft_strlcpy(res_str + str_len_1, s2, str_len_2 + 1);
	return (res_str);
}
