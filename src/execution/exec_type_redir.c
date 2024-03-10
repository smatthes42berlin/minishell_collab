#include "minishell.h"

static int	handle_exec(int fd, t_main_data *data, t_node_redir *redir_node,
				t_pipefd *pipe_struct);
static int	open_handler(t_main_data *data, t_node_redir *redir_node,
				t_pipefd *pipe_struct);
//static void	set_error_open_handler(t_main_data *data, t_node_redir *redir_node,
//				t_pipefd *pipe_struct);
static int	creat_and_throw_error(const char *path, int errnum);

int	type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_redir	*redir_node;
	int				fd;
	char			*err_msg;
	int				ret;

	ret = 0;
	err_msg = "function \"type_redir\"";
	redir_node = (t_node_redir *)node;
	fd = open_handler(data, redir_node, pipe_struct);
	if (fd == 1)
	{
		return (1);
	}
	if (use_dup2(fd, redir_node->in_or_out, err_msg) != 0)
	{
		use_close(fd, err_msg);
		return (-1);
	}
	if (redir_node->left_node == NOTHING)
	{
		printf("NO CHILD IN REDIR!\n");
		return (0);
		// set 0
	}
	else
	{
		ret = handle_exec(fd, data, redir_node, pipe_struct);
		return (ret);
	// use_close(fd, "function \"type_redir\"");
	}
	return (ret);
}

static int	handle_exec(int fd, t_main_data *data, t_node_redir *redir_node,
		t_pipefd *pipe_struct)
{
	//char	*err_msg;
	int		ret;

	// pid_t	cpid;
	// int		status;
	if (fd == 194464)
		printf("bullshit");
	//err_msg = "function handle_exec -> type_redir";
	// cpid = fork_handler(err_msg);
	// if (cpid == 0)
	// {



	use_close(fd, "function \"type_redir\"");
	ret = 0;
	if (redir_node->left_node->type == EXEC)
		ret = type_exec(data, redir_node->left_node, pipe_struct, true);
	// else if (redir_node->left_node->type == REDIR)
	// {
	// 	ret = type_redir(data, redir_node->left_node, pipe_struct);
	// }
	else
		ret = navigate_tree_forward(data, redir_node->left_node, pipe_struct);
	// }
	// else
	// {
	// 	waitpid(cpid, &status, 0);
	// 	if (is_last_node_redir(data->ast, redir_node->filename))
	// 		write_exit_status_to_pipe(status, pipe_struct, err_msg);
	// }


	/*
		return file check or 
	*/

    // Drucken des Rückgabewerts auf der Konsole
   //printf("return redir > %d\n", ret);


	return (ret);
}

static int	open_handler(t_main_data *data, t_node_redir *redir_node,
		t_pipefd *pipe_struct)
{
	int	result;
	int ret;

	ret = 0;
	if (!data && !redir_node && !pipe_struct)
		printf("asdasd");
	if (redir_node->mode == FILE_ONLY_READING)
	{
		result = access_handler(redir_node->filename, FILE_EXISTS, 0);
		if (result == 0)
			result = open(redir_node->filename, redir_node->mode);
		else
		{
			creat_and_throw_error(redir_node->filename, errno);
			return (1);
		}
	}
	else
	{
		result = access_handler(redir_node->filename, FILE_EXISTS, 0);
		if (result >= 0)
			result = open(redir_node->filename, redir_node->mode);
		else
			result = open(redir_node->filename, redir_node->mode | O_CREAT,
					0644);
	}
	if (result < 0)
	{
		creat_and_throw_error(redir_node->filename, errno);
		return (1);
	}
	//printf("resust fromt redir %d  return value %i filename |%s| \n", result, ret, redir_node->filename);
	return (ret);
}

// static void	set_error_open_handler(t_main_data *data, t_node_redir *redir_node,
// 		t_pipefd *pipe_struct)
// {
// 	int			exit_code;
// 	char		*err_msg;
// 	t_list_d	*token_list;
// 	t_token		*last_tocken;
// 	char		*last_value;

// 	token_list = d_lst_last(data->token_list);
// 	last_tocken = (t_token *)token_list->content;
// 	last_value = last_tocken->value;
// 	//printf("\nLast Node: %s\n", last_value);
// 	err_msg = "function set_error_open_handler -> type_redir";
// 	if (str_are_equal(last_value, redir_node->filename))
// 	{
// 		exit_code = 1;
// 		//printf("Setting exit code %d\necho", exit_code);
// 		pipe_setting_exit_code(pipe_struct->pipefd_exit_code, true, &exit_code,
// 			err_msg);
// 	}
// 	return ;
// }

static int	creat_and_throw_error(const char *path, int errnum)
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
	return (1);
}
