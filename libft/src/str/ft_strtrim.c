#include "lib_main.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res_str;
	size_t	set_len;
	size_t	s1_len;
	size_t	rem_c_start;
	size_t	rem_c_end;

	rem_c_start = 0;
	rem_c_end = 0;
	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	if (set_len == 0 || s1_len == 0 || set_len > s1_len)
		return (ft_strdup(s1));
	while (ft_strchr((char *)set, s1[rem_c_start]) != NULL)
		rem_c_start += 1;
	while (ft_strrchr((char *)set, s1[s1_len - rem_c_end - 1]) != NULL)
		rem_c_end += 1;
	res_str = ft_substr(s1, rem_c_start, s1_len - rem_c_start - rem_c_end);
	return (res_str);
}
