#include "./lib_main.h"

static int		get_substr_len(char const *s, char c);
static int		create_sub_str(char **res, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	num_substr;

	res = NULL;
	num_substr = ft_split_num_substr(s, c);
	res = malloc(sizeof(*res) * (num_substr + 1));
	if (!res)
		return (NULL);
	if (!create_sub_str(res, s, c))
		return (NULL);
	res[num_substr] = NULL;
	return (res);
}

static int	create_sub_str(char **res, char const *s, char c)
{
	int		i_str;
	size_t	i_num_substr;
	size_t	substr_len;

	i_str = 0;
	i_num_substr = 0;
	while (s[i_str])
	{
		if (s[i_str] != c)
		{
			substr_len = get_substr_len(s + i_str, c);
			if (!malloc_error_free(res, i_num_substr, substr_len))
				return (0);
			ft_strlcpy(res[i_num_substr], s + i_str, substr_len + 1);
			i_num_substr++;
			i_str += substr_len;
		}
		else
			i_str++;
	}
	return (1);
}

static int	get_substr_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}
