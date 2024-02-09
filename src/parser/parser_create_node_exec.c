
#include "minishell.h"

static int	init_exec_node_param(t_parse_info *parse_info,
								t_node_exec *exec_node);

// typedef struct s_node_exec
// {
// 	char				*file_path;
// 	char				**argv;
// 	char				**env;
// 	bool				is_inbuilt;
// }						t_node_exec;

// checken, ob command existiert
// auch checken, dass command kein file ist
// eventuell checken, ob man Zugriff auf Command hat
// argument von den naechsten Token holen
// use stat with filename to check permissions for file
// check, whether command is inbuilt

int	create_exec_node(t_parse_info *parse_info)
{
	t_node_exec	*exec_node;

	exec_node = malloc(sizeof(t_node_exec));
	if (!exec_node)
		return (printf("Error: Allocating memory for exec node \n"));
	init_generic_node_param((t_node *)exec_node, EXEC);
	if (init_exec_node_param(parse_info, exec_node))
		return (1);
	if (check_if_inbuilt(exec_node))
		return (1);
	if (check_if_cmd_exists(exec_node))
		return (1);
	if (get_cmd_arguments(parse_info, exec_node))
		return (1);
	// if (check_access_if_cmd_is_folder(parse_info, exec_node))
	// 	return (1);
	if (add_all_but_pipe_ast(parse_info, (t_node *)exec_node))
		return (1);
	print_exec_node(exec_node, 1);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}

int	check_if_inbuilt(t_node_exec *exec_node)
{
	if (!ft_strcmp(exec_node->file_path, "echo")
		|| !ft_strcmp(exec_node->file_path, "cd")
		|| !ft_strcmp(exec_node->file_path, "pwd")
		|| !ft_strcmp(exec_node->file_path, "export")
		|| !ft_strcmp(exec_node->file_path, "unset")
		|| !ft_strcmp(exec_node->file_path, "env")
		|| !ft_strcmp(exec_node->file_path, "exit"))
	{
		exec_node->is_inbuilt = true;
		exec_node->file_path = ft_strdup(exec_node->file_path);
		if (!exec_node->file_path)
			return (printf("error copying exe name when inbuilt recognised\n"));
	}
	else
		exec_node->is_inbuilt = false;
	return (0);
}

static int	init_exec_node_param(t_parse_info *parse_info,
								t_node_exec *exec_node)
{
	exec_node->argv = NULL;
	exec_node->file_path = parse_info->cur_token->value;
	exec_node->is_inbuilt = false;
	exec_node->env = ft_arr_cpy_char_null(parse_info->main_data->env_vars);
	if (!exec_node->env && parse_info->main_data->env_vars)
		return (printf("Error copying the envrionment from main process to exec node\n"));
	return (0);
}

int	check_if_cmd_exists(t_node_exec *exec_node)
{
	char	*path;

	if (exec_node->is_inbuilt)
		return (0);
	if (check_cmd_access(exec_node->env, exec_node->file_path, &path))
		return (1);
	if (!path)
		exec_node->file_path = NULL;
	else
		exec_node->file_path = path;
	return (0);
}

int	get_cmd_arguments(t_parse_info *parse_info,
						t_node_exec *exec_node)
{
	t_list_d	*lst;
	t_token		*token;

	lst = parse_info->next->next;
	token = lst->content;
	if (exec_node->file_path)
		if (copy_argument(exec_node, exec_node->file_path))
			return (1);
	while (lst && !token_is_pipe(token))
	{
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
		if (lst)
			token = lst->content;
	}
	return (0);
}

int	copy_argument(t_node_exec *exec_node, char *new_arg)
{
	char	**tmp;

	tmp = ft_arr_char_add(exec_node->argv, new_arg);
	if (!tmp)
		return (printf("Error adding an argument to exec node arg list"));
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
