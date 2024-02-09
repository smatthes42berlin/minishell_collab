#include "lib_main.h"

int	ft_str_n_dup_int(const char *s, int n, char **res)
{
	size_t	str_len;
	int		i;

	i = 0;
	*res = NULL;
	if (!s)
		return (1);
	if (n <= 0)
	{
		str_len = ft_strlen(s);
		n = str_len + 1;
	}
	*res = malloc((n) * sizeof(**res));
	if (!(*res))
		return (-1);
	while (s[i] && i < n - 1)
	{
		(*res)[i] = s[i];
		i++;
	}
	(*res)[i] = '\0';
	return (1);
}
