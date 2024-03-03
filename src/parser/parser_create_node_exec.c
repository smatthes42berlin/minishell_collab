#include "minishell.h"

static int	init_exec_node_param(t_parse_info *parse_info,
				t_node_exec *exec_node);

int	create_exec_node(t_parse_info *parse_info)
{
	t_node_exec	*exec_node;

	exec_node = malloc(sizeof(t_node_exec));
	if (!exec_node)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "exec node"}));
	init_generic_node_param((t_node *)exec_node, EXEC);
	if (init_exec_node_param(parse_info, exec_node))
		return (free_exec_code_during_creation(exec_node, 1));
	if (check_if_inbuilt(exec_node))
		return (free_exec_code_during_creation(exec_node, 1));
	if (check_if_cmd_exists(exec_node))
		return (free_exec_code_during_creation(exec_node, 1));
	if (get_cmd_arguments(parse_info, exec_node))
		return (free_exec_code_during_creation(exec_node, 1));
	if (check_if_cmd_is_folder(exec_node))
		return (free_exec_code_during_creation(exec_node, 1));
	add_all_but_pipe_ast(parse_info, (t_node *)exec_node);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}

int	free_exec_code_during_creation(t_node_exec *exec_node, int code)
{
	free(exec_node->file_path);
	free(exec_node->file_path_org);
	free_str_arr_null(exec_node->env);
	free_str_arr_null(exec_node->argv);
	return (code);
}

int	check_if_cmd_is_folder(t_node_exec *exec_node)
{
	struct stat	statbuf;

	if (!exec_node->file_path || exec_node->is_inbuilt)
		return (0);
	if (stat(exec_node->file_path, &statbuf))
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER, EFUNC_STAT,
				"exec node checking file info"}));
	if (S_ISDIR(statbuf.st_mode))
	{
		free(exec_node->file_path);
		exec_node->file_path = NULL;
		exec_node->is_folder = true;
	}
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
		exec_node->is_inbuilt = true;
	else
		exec_node->is_inbuilt = false;
	return (0);
}

static int	init_exec_node_param(t_parse_info *parse_info,
								t_node_exec *exec_node)
{
	exec_node->argv = NULL;
	exec_node->is_folder = false;
	exec_node->file_path = ft_strdup(parse_info->cur_token->value);
	exec_node->file_path_org = ft_strdup(parse_info->cur_token->value);
	if (!exec_node->file_path || !exec_node->file_path_org)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "copying token val exec node"}));
	exec_node->is_inbuilt = false;
	exec_node->env = ft_arr_cpy_char_null(parse_info->main_data->env_vars);
	if (!exec_node->env && parse_info->main_data->env_vars)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "copying environment  exec node"}));
	return (0);
}
