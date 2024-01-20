#include "lib_main.h"

char	*ft_str_n_dup(const char *s, int n)
{
	size_t	str_len;
	char	*new_str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (n == 0)
	{
		str_len = ft_strlen(s);
		n = str_len + 1;
	}
	new_str = malloc((n) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	while (s[i] && i < n - 1)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
