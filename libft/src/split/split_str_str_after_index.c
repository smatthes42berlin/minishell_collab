#include "./lib_main.h"

static int	dup_otherwise_empty(char ***res, char const *str1,
				char const *str2);
static int	free_res(char ***res, int ret_code, int free_what);
static int	handle_empty_strings(char const *s, char const *split_at,
				char ***res);

int	split_str_str_after_index(char const *s, char const *split_at, char ***res,
		int index)
{
	int	split_start;
	int	split_at_len;

	*res = NULL;
	split_at_len = ft_strlen(split_at);
	if (!s || !split_at)
		return (-1);
	*res = malloc(sizeof(**res) * 2);
	if (!*res)
		return (1);
	if (str_is_empty(s) || str_is_empty(split_at))
		return (handle_empty_strings(s, split_at, res));
	split_start = str_contains_str_index(s + index, split_at) + index;
	if (split_start == -1)
		return (dup_otherwise_empty(res, s, NULL));
	if (split_start == 0)
		return (dup_otherwise_empty(res, NULL, s + split_at_len));
	if (ft_str_n_dup_int(s, split_start + 1, &((*res)[0])) == -1)
		return (free_res(res, 4, 0));
	if (ft_str_n_dup_int((s + split_start + split_at_len), 0, &((*res)[1])) ==
		-1)
		return (free_res(res, 5, 1));
	return (0);
}

static int	handle_empty_strings(char const *s, char const *split_at,
		char ***res)
{
	if (str_is_empty(s) && str_is_empty(split_at))
		return (dup_otherwise_empty(res, NULL, NULL));
	if (str_is_empty(split_at))
		return (dup_otherwise_empty(res, s, NULL));
	if (str_is_empty(s))
		return (dup_otherwise_empty(res, s, NULL));
	return (6);
}

static int	dup_otherwise_empty(char ***res, char const *str1, char const *str2)
{
	if (!str1)
		str1 = "";
	if (!str2)
		str2 = "";
	(*res)[0] = ft_strdup(str1);
	if (!(*res)[0])
		return (free_res(res, 2, 0));
	(*res)[1] = ft_strdup(str2);
	if (!(*res)[1])
		return (free_res(res, 3, 1));
	return (0);
}

static int	free_res(char ***res, int ret_code, int free_what)
{
	if (free_what >= 1)
		free((*res)[0]);
	free(*res);
	return (ret_code);
}
