#include "minishell.h"

static	int	type_redir_exec(t_main_data *data,
				t_node_redir *redir_node, t_pipefd *pipe_struct, int fd);
static int	handle_exec(t_main_data *data, t_node_redir *redir_node,
				t_pipefd *pipe_struct);
static int	open_handler(const char *path, enum e_open_mode mode);
static int	creat_and_throw_error(const char *path, int errnum);

int	type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_redir	*redir_node;
	int				fd;
	char			*err_msg;

	err_msg = "function \"type_redir\"";
	redir_node = (t_node_redir *)node;
	fd = open_handler(redir_node->filename, redir_node->mode);
	if (fd < 0)
	{
		if (redir_node->in_or_out == STDIN && redir_node->is_last_node == true)
			return (0);
		else
			return (1);
	}
	if (use_dup2(fd, redir_node->in_or_out, err_msg) != 0)
	{
		use_close(fd, err_msg);
		return (-1);
	}
	return (type_redir_exec(data, redir_node, pipe_struct, fd));
}

static	int	type_redir_exec(t_main_data *data,
		t_node_redir *redir_node, t_pipefd *pipe_struct, int fd)
{
	int	ret;

	if (redir_node->is_last_node == 1 || redir_node->left_node == NULL)
		ret = 0;
	else
		ret = handle_exec(data, redir_node, pipe_struct);
	use_close(fd, "function \"type_redir\"");
	return (ret);
}

static int	handle_exec(t_main_data *data, t_node_redir *redir_node,
		t_pipefd *pipe_struct)
{
	int		ret;

	if (redir_node->left_node->type == EXEC)
		ret = type_exec(data, redir_node->left_node, pipe_struct, true);
	else
		ret = navigate_tree_forward(data, redir_node->left_node, pipe_struct);
	return (ret);
}

static int	open_handler(const char *path, enum e_open_mode mode)
{
	int	result;

	result = 0;
	if (mode == FILE_ONLY_READING)
	{
		result = access_handler(path, FILE_EXISTS, 0);
		if (result == 0)
			result = open(path, mode);
		else
			return (creat_and_throw_error(path, errno));
	}
	else
	{
		result = access_handler(path, FILE_EXISTS, 0);
		if (result == 0)
			result = open(path, mode);
		else
			result = open(path, mode | O_CREAT, 0644);
	}
	if (result < 0)
		return (creat_and_throw_error(path, errno));
	return (result);
}

static int	creat_and_throw_error(const char *path, int errnum)
{
	char	*err_msg;
	char	*tmp_str;
	char	*err_msg_strjoin;

	err_msg_strjoin = "function creat_and_throw_error -> executor";
	tmp_str = use_strjoin("minishell: ", path, err_msg_strjoin);
	err_msg = use_strjoin(tmp_str, ": ", err_msg_strjoin);
	free(tmp_str);
	tmp_str = use_strjoin(err_msg, strerror(errnum), err_msg_strjoin);
	free(err_msg);
	err_msg = use_strjoin(tmp_str, "\n", err_msg);
	if (write(STDERR_FILENO, err_msg, strlen(err_msg)) < 0)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_WRITE,
			"function write err output in redir"});
	set_exit_code(1);
	free(tmp_str);
	free(err_msg);
	return (-1);
}
