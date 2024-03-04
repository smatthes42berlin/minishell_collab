#include "minishell.h"

int	get_cmd_arguments(t_parse_info *parse_info, t_node_exec *exec_node)
{
	t_list_d	*lst;
	t_token		*token;

	lst = parse_info->next->next;
	if (copy_cmd_name_to_args_arr(exec_node))
		return (1);
	while (lst)
	{
		if (lst)
			token = lst->content;
		if (token_is_pipe(token))
			break ;
		if (token_is_redir(token))
			got_to_nth_next_lst(&lst, 2);
		else if (token_is_here_doc(token))
			got_to_nth_next_lst(&lst, 1);
		else
		{
			token->parsed = true;
			if (copy_argument(exec_node, token->value))
				return (1);
			got_to_nth_next_lst(&lst, 1);
		}
	}
	return (0);
}

int	copy_cmd_name_to_args_arr(t_node_exec *exec_node)
{
	if (exec_node->file_path)
	{
		if (copy_argument(exec_node, exec_node->file_path))
			return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
					EFUNC_MALLOC,
					"exec node adding an argument to exec node arg list"}));
	}
	else
	{
		if (copy_argument(exec_node, exec_node->file_path_org))
			return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
					EFUNC_MALLOC,
					"exec node adding an argument to exec node arg list"}));
	}
	return (0);
}

int	copy_argument(t_node_exec *exec_node, char *new_arg)
{
	char	**tmp;

	tmp = ft_arr_char_add(exec_node->argv, new_arg);
	if (!tmp)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC,
				"exec node adding an argument to exec node arg list"}));
	free_str_arr_null(exec_node->argv);
	exec_node->argv = tmp;
	return (0);
}

int	got_to_nth_next_lst(t_list_d **lst, int n)
{
	while (n > 0)
	{
		*lst = (*lst)->next;
		n--;
	}
	return (0);
}

int	check_if_cmd_exists(t_node_exec *exec_node)
{
	char	*path;
	char	*tmp;

	if (exec_node->is_inbuilt)
		return (0);
	if (check_cmd_access(exec_node->env, exec_node->file_path, &path))
		return (1);
	tmp = exec_node->file_path;
	exec_node->file_path = path;
	free(tmp);
	return (0);
}
