#include "lib_main.h"

char	*ft_strdup(const char *s)
{
	size_t	str_len;
	char	*new_str;

	str_len = ft_strlen(s);
	new_str = malloc((str_len + 1) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	new_str[str_len] = '\0';
	while (str_len > 0)
	{
		new_str[str_len - 1] = s[str_len - 1];
		str_len--;
	}
	return (new_str);
}
