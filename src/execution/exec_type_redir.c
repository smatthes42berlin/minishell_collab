#include "minishell.h"

void	type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_redir	*redir_node;
	int				fd;

	print_debugging_info_executer(INT_DEBUG, 5, NULL);
	redir_node = (t_node_redir *)node;
	fd = open_handler(redir_node->filename, redir_node->mode);
	if (fd == -1)
	{
		error_code_handler(errno, "ERR-open_handler in \"type_redir\"", "", "");
		return ;
	}
	if (dup2(fd, redir_node->in_or_out) == -1)
	{
		close_handler(fd);
		error_code_handler(errno, "ERR-dub_2 in \"type_redir\"", "", "");
		return ;
	}
	if (redir_node->left_node->type == NOTHING)
		return ;
	else
		navigate_tree_forward(data, redir_node->left_node, pipe_struct);
	close_handler(fd);
}