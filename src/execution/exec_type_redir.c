#include "minishell.h"

static int	open_handler(const char *path, enum e_open_mode mode, int debug);

void	type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_redir	*redir_node;
	int				fd;

	print_debugging_info_executer(INT_DEBUG, 5, NULL);
	redir_node = (t_node_redir *)node;
	fd = open_handler(redir_node->filename, redir_node->mode , INT_DEBUG);
	if (fd < 0)
	{
		return ;
	}
	if (use_dup2(fd, redir_node->in_or_out, "function \"type_redir\"") != 0)
	{
		use_close(fd, "function \"type_redir\"");
		return ;
	}
	if (redir_node->left_node->type == NOTHING)
		return ;
	else
		navigate_tree_forward(data, redir_node->left_node, pipe_struct);
	use_close(fd, "function \"type_redir\"");
}


static int	open_handler(const char *path, enum e_open_mode mode, int debug)
{
	int 	result;
	char 	*err_msg;
	char 	*tmp_str;

	result = -1;
	if (mode == FILE_ONLY_READING)
	{
		if (access_handler(path, FILE_EXISTS, INT_DEBUG) == 0)
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
		}
	}
	else
		result = open(path, mode | O_CREAT, 0644);
	if (result < 0 && debug)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_OPEN,
			"function \"type_redir\""});
	return (result);
}