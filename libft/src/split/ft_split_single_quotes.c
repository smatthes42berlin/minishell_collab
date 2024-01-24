#include "./lib_main.h"

static int	get_substr_len(char const *s, char c);
static int	create_sub_str_sq(char **res, char const *s, char c);
static int	inside_single_quotes(t_split_sq *data);
static int	outside_single_quotes(t_split_sq *data);

char	**ft_split_single_quotes(char const *s, char c)
{
	char	**res;
	size_t	num_substr;

	res = NULL;
	num_substr = ft_split_num_substr_sq(s, c);
	res = malloc(sizeof(*res) * (num_substr + 1));
	if (!res)
		return (NULL);
	if (!create_sub_str_sq(res, s, c))
		return (NULL);
	res[num_substr] = NULL;
	return (res);
}

static int	create_sub_str_sq(char **res, char const *s, char c)
{
	t_split_sq	data;

	data.i_str = 0;
	data.i_num_substr = 0;
	data.s = s;
	data.c = c;
	data.res = res;
	while (s[data.i_str])
	{
		if (s[data.i_str] == '\'' && ((data.i_str == 0) || s[data.i_str
					- 1] == c))
		{
			if (inside_single_quotes(&data) == -1)
				return (-1);
		}
		else if (s[data.i_str] != c)
		{
			if (outside_single_quotes(&data) == -1)
				return (-1);
		}
		else
			data.i_str++;
	}
	return (1);
}

static int	inside_single_quotes(t_split_sq *data)
{
	size_t	substr_len;

	(data->i_str)++;
	substr_len = get_substr_len(data->s + data->i_str, '\'');
	if (substr_len == 0)
	{
		(data->i_str)++;
		return (1);
	}
	if (!malloc_error_free(data->res, data->i_num_substr, substr_len))
		return (-1);
	ft_strlcpy(data->res[data->i_num_substr], data->s + data->i_str, substr_len
		+ 1);
	(data->i_num_substr)++;
	data->i_str += (substr_len + 1);
	return (1);
}

static int	outside_single_quotes(t_split_sq *data)
{
	data->substr_len = get_substr_len(data->s + data->i_str, data->c);
	if (!malloc_error_free(data->res, data->i_num_substr, data->substr_len))
		return (-1);
	ft_strlcpy(data->res[data->i_num_substr], data->s + data->i_str,
		data->substr_len + 1);
	data->i_num_substr++;
	data->i_str += data->substr_len;
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
