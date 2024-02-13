#include "minishell.h"

int		read_file(int fd);

void	type_heredoc(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_heredoc	*heredoc_node;

	print_debugging_info_executer(INT_DEBUG, 29, NULL);
	heredoc_node = (t_node_heredoc *)node;
	//read_file(heredoc_node->read_fd);
	if (dup2(heredoc_node->read_fd, STDIN_FILENO) == -1)
	{
		close_handler(heredoc_node->read_fd);
		error_code_handler(errno, "ERR-dub_2 in \"type_redir\"", "", "");
		return ;
	}
	if (heredoc_node->left_node->type == NOTHING)
	{
		printf("NOTHING exec Command behind Redir Node!\n");
		return ;
	}
	else
		navigate_tree_forward(data, heredoc_node->left_node, pipe_struct);
	close_handler(heredoc_node->read_fd);
}

int	read_file(int fd)
{
	char buffer[1024];

	ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead < 0)
	{
		perror("Fehler beim Lesen vom File Descriptor");
		exit(EXIT_FAILURE);
	}
	buffer[bytesRead] = '\0';
	printf("Gelesener Text: %s\n", buffer);
	return (0);
}