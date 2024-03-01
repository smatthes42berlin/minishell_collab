#include "minishell.h"

static void	handle_exec(t_main_data *data, t_node_redir *redir_node,
				t_pipefd *pipe_struct);
static int	open_handler(const char *path, enum e_open_mode mode);
static void	set_error_open_handler(t_main_data *data, t_node_redir *redir_node,
				t_pipefd *pipe_struct);
static void	creat_and_throw_error(const char *path, int errnum);

void	type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_redir	*redir_node;
	int				fd;
	char			*err_msg;

	err_msg = "function \"type_redir\"";
	print_debugging_info_executer(INT_DEBUG, 5, NULL);
	redir_node = (t_node_redir *)node;
	fd = open_handler(redir_node->filename, redir_node->mode);
	if (fd < 0)
	{
		set_error_open_handler(data, redir_node, pipe_struct);
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
		handle_exec(data, redir_node, pipe_struct);
	use_close(fd, "function \"type_redir\"");
	return ;
}

static void	handle_exec(t_main_data *data, t_node_redir *redir_node,
		t_pipefd *pipe_struct)
{
	pid_t	cpid;
	int		status;
	int		exit_code;
	char	*err_msg;

	err_msg = "function handle_exec -> type_redir";
	cpid = fork_handler(err_msg);
	if (cpid == 0)
		navigate_tree_forward(data, redir_node->left_node, pipe_struct);
	else
	{
		waitpid(cpid, &status, 0);
		if (data->ast->type == REDIR)
		{
			exit_code = get_process_exit_code(status);
			pipe_setting_exit_code(pipe_struct->pipefd_exit_code, true,
				&exit_code, err_msg);
		}
	}
	return ;
}

static int	open_handler(const char *path, enum e_open_mode mode)
{
	int	result;

	result = -1;
	if (mode == FILE_ONLY_READING)
	{
		result = access_handler(path, FILE_EXISTS, INT_DEBUG);
		if (result == 0)
			result = open(path, mode);
		else
		{
			creat_and_throw_error(path, errno);
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
		creat_and_throw_error(path, errno);
	return (result);
}

static void	set_error_open_handler(t_main_data *data, t_node_redir *redir_node,
		t_pipefd *pipe_struct)
{
	int		exit_code;
	char	*err_msg;

	err_msg = "function set_error_open_handler -> type_redir";
	if (is_last_node_redir(data->ast, redir_node->filename)
		|| data->ast->type == REDIR)
	{
		exit_code = 1;
		pipe_setting_exit_code(pipe_struct->pipefd_exit_code, true, &exit_code,
			err_msg);
	}
	return ;
}

static void	creat_and_throw_error(const char *path, int errnum)
{
	char	*err_msg;
	char	*tmp_str;
	char	*err_msg_strjoin;

	err_msg_strjoin = "function creat_and_throw_error -> executor";
	err_msg = use_strjoin("minishell: ", path, err_msg_strjoin);
	tmp_str = use_strjoin(err_msg, ": ", err_msg_strjoin);
	free(err_msg);
	err_msg = use_strjoin(tmp_str, strerror(errnum), err_msg_strjoin);
	throw_error_mimic_bash(err_msg, 1);
	free(tmp_str);
	free(err_msg);
	return ;
}
