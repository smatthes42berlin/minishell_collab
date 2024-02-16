#include "./lib_main.h"

static size_t	calc_num_substr(char const *s, char const *split_at,
					size_t *num_substr, size_t split_at_length);
static int		get_substr_len(char const *s, char const *split_at,
					size_t split_at_length);
static int		create_sub_str(char **res, char const *s, char const *split_at,
					size_t split_at_length);
static int		split_at_occurs(char const *str, char const *split_at,
					size_t split_at_length);

char	**ft_split_str(char const *s, char const *split_at)
{
	char	**res;
	size_t	num_substr;
	size_t	split_at_length;

	res = NULL;
	if (!s || !split_at)
		return (res);
	split_at_length = ft_strlen(split_at);
	num_substr = 0;
	calc_num_substr(s, split_at, &num_substr, split_at_length);
	res = malloc(sizeof(*res) * (num_substr + 1));
	if (!res)
		return (res);
	if (!create_sub_str(res, s, split_at, split_at_length))
		return (NULL);
	res[num_substr] = NULL;
	return (res);
}

static int	create_sub_str(char **res, char const *s, char const *split_at,
		size_t split_at_length)
{
	size_t	i_str;
	size_t	i_num_substr;
	size_t	substr_len;

	i_str = 0;
	i_num_substr = 0;
	while (s[i_str])
	{
		if (!split_at_occurs(&s[i_str], split_at, split_at_length))
		{
			substr_len = get_substr_len(s + i_str, split_at, split_at_length);
			if (!malloc_error_free(res, i_num_substr, substr_len))
				return (0);
			ft_strlcpy(res[i_num_substr], s + i_str, substr_len + 1);
			i_num_substr++;
			i_str = i_str + substr_len;
		}
		else
			i_str += split_at_length;
	}
	return (1);
}

static int	get_substr_len(char const *s, char const *split_at,
		size_t split_at_length)
{
	int	len;

	len = 0;
	while (s[len] && !split_at_occurs(&s[len], split_at, split_at_length))
		len++;
	return (len);
}

static size_t	calc_num_substr(char const *s, char const *split_at,
		size_t *num_substr, size_t split_at_length)
{
	size_t	state;
	int		i;

	i = 0;
	state = 0;
	while (s[i])
	{
		while (s[i] && split_at_occurs(&s[i], split_at, split_at_length))
		{
			i += split_at_length;
			state = 0;
		}
		if (s[i])
		{
			i++;
			if (state == 0)
			{
				(*num_substr)++;
				state = 1;
			}
		}
	}
	return (*num_substr);
}

static int	split_at_occurs(char const *str, char const *split_at,
		size_t split_at_length)
{
	char	*sub_str;
	int		cmp_res;

	if (split_at_length == 0)
		return (0);
	sub_str = ft_substr(str, 0, split_at_length);
	cmp_res = ft_strncmp(sub_str, split_at, split_at_length);
	free(sub_str);
	if (cmp_res == 0)
		return (1);
	return (0);
}
