#include "lib_main.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			str_len;
	char			*substr;
	unsigned int	sub_len;

	str_len = ft_strlen(s);
	if (len == 0 || str_len == 0 || str_len <= start)
		return (ft_strdup(""));
	if (str_len < (start + len))
		sub_len = str_len - start;
	else
		sub_len = len;
	substr = malloc(sizeof(*substr) * (sub_len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (s + start), sub_len + 1);
	return (substr);
}
