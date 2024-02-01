#include "./lib_main.h"

static int	init_vals(t_arr_char_key_info *arr_info, int *i, int *j,
				char **org_arr);

char	**ft_arr_char_rem_n(char **arr, char *val)
{
	t_arr_char_key_info	arr_info;
	int					i;
	int					j;

	arr_info.val = val;
	if (init_vals(&arr_info, &i, &j, arr))
		return (NULL);
	while (i < arr_info.arr_len)
	{
		if (!ft_strncmp(arr[i], val, arr_info.key_len))
			i++;
		else
		{
			arr_info.cpy[j] = ft_strdup(arr[i]);
			if (!arr_info.cpy[j])
			{
				free_str_arr_null(arr_info.cpy);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	arr_info.cpy[j] = NULL;
	return (arr_info.cpy);
}

static int	init_vals(t_arr_char_key_info *arr_info, int *i, int *j,
		char **org_arr)
{
	arr_info->cpy = NULL;
	arr_info->key_len = ft_str_chr_index(arr_info->val, '=');
	if (arr_info->key_len < 0)
		arr_info->key_len = ft_strlen(arr_info->val);
	arr_info->arr_len = ft_arr_len_char(org_arr);
	arr_info->key_occ_n = ft_arr_char_occ_num_n(org_arr, arr_info->val);
	*i = 0;
	*j = 0;
	(*arr_info).cpy = malloc(sizeof(*arr_info->cpy) * ((*arr_info).arr_len + 1
				- (*arr_info).key_occ_n));
	if (!(*arr_info).cpy)
		return (1);
	return (0);
}
