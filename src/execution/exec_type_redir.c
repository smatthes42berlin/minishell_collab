#include "minishell.h"

static int	open_handler(const char *path, enum e_open_mode mode);

void	type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_redir	*redir_node;
	int				fd;
	int				exit_code;
	pid_t			cpid;
	char			*err_msg;
	int				status;

	err_msg = "function \"type_redir\"";

	print_debugging_info_executer(INT_DEBUG, 5, NULL);
	redir_node = (t_node_redir *)node;
	fd = open_handler(redir_node->filename, redir_node->mode);
	if (fd < 0)
	{
		if (is_last_node_redir(data->ast, redir_node->filename) || data->ast->type == REDIR)
		{
			exit_code = 1;
			pipe_setting_exit_code(pipe_struct->pipefd_exit_code, true, &exit_code, err_msg);
		}
		return ;
	}
	if (use_dup2(fd, redir_node->in_or_out, err_msg) != 0)
	{
		use_close(fd, err_msg);
		return ;
	}
	if (redir_node->left_node->type == NOTHING)
		return ;
	else
	{
		cpid = fork_handler(err_msg);
		if (cpid == 0)
			navigate_tree_forward(data, redir_node->left_node, pipe_struct);
		else
		{
			waitpid(cpid, &status, 0);
			if (data->ast->type == REDIR)
			{
				exit_code = get_process_exit_code(status);
				pipe_setting_exit_code(pipe_struct->pipefd_exit_code, true, &exit_code, err_msg);
			}
		}
	}
	use_close(fd, "function \"type_redir\"");
}


static int	open_handler(const char *path, enum e_open_mode mode)
{
	int 	result;
	char 	*err_msg;
	char 	*tmp_str;

	result = -1;
	if (mode == FILE_ONLY_READING)
	{
		result = access_handler(path, FILE_EXISTS, INT_DEBUG);
		
		if (result == 0)
			result = open(path, mode);
		else
		{
			err_msg = ft_strjoin("minishell: ", path);
			tmp_str = ft_strjoin(err_msg, ": ");
			free(err_msg);
			err_msg = ft_strjoin(tmp_str, strerror(errno));
			throw_error_mimic_bash(err_msg, 1);
			free(tmp_str);
			free(err_msg);
			return (result);
		}

	}
	else
	{
		result = access_handler(path, FILE_EXISTS, INT_DEBUG);

		if (result == 0)
			result = open(path, mode);
		else
			result = open(path, mode | O_CREAT, 0644);
	}
	if (result < 0)
	{
			err_msg = ft_strjoin("minishell: ", path);
			tmp_str = ft_strjoin(err_msg, ": ");
			free(err_msg);
			err_msg = ft_strjoin(tmp_str, strerror(errno));
			throw_error_mimic_bash(err_msg, 1);
			free(tmp_str);
			free(err_msg);
	}
	//printf("access result %i !\n", result);
	return (result);
}