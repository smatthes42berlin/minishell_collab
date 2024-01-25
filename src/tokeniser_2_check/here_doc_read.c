#include "minishell.h"

// make pipe
// fork
// read all lines in child
// write string to pipe
// write first value as stringlength
// free in child
// exit child
// read string in parent

int	read_heredoc(t_here_doc_info *hdoc_info, t_list_d **hdoc_op_token)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (printf("Error: creating pipe"));
	pid = fork();
	if (pid == -1)
		return (printf("Error: forking"));
	if (pid == 0)
	{
		if (close(fd[0]) == -1)
			return (printf("Error: closing pipe"));
		return (child_read_hdoc(hdoc_info, fd));
	}
	else
	{
		if (close(fd[1]) == -1)
			return (printf("Error: closing pipe"));
		return (parent_get_str_child(hdoc_op_token, fd, pid));
	}
	// printf("1: $%s$\n", hdoc_info->delim_raw);
}

int	parent_get_str_child(t_list_d **hdoc_op_token, int fd[2], int pid)
{
	int		res_wait;
	int		status;
	char	*res;

	res_wait = waitpid(pid, &status, 0);
	if (res_wait == -1)
		printf("Error: problem waiting for child process");
	if (WIFEXITED(status))
		res_wait = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		res_wait = WTERMSIG(status);
	if (read_whole_file(fd[0], &res))
		return (printf("Error: reading from pipe"));
	if (close(fd[0]) == -1)
		return (printf("Error: closing pipe"));
	if (add_heredoc_str_token(hdoc_op_token, res))
		return (printf("Error: problem manipulating linked list heredoc"));
	printf("res par = $%s$\n", res);
	return (0);
}

int	add_heredoc_str_token(t_list_d **hdoc_op_token, char *res)
{
	t_list_d	*next_token;
	t_token		*next_token_val;

	next_token = (*hdoc_op_token)->next;
	next_token_val = next_token->content;
	next_token_val->value = res;
	return (0);
}

int	child_read_hdoc(t_here_doc_info *hdoc_info, int fd[2])
{
	char	*compl_str;
	char	*tmp;
	char	*new_line;
	bool	eof;
	int		str_len;

	eof = false;
	printf("%s\n", hdoc_info->delim);
	compl_str = NULL;
	while (!eof)
	{
		new_line = readline(">");
		if (ft_strcmp(new_line, hdoc_info->delim) == 0)
		{
			str_len = ft_strlen(compl_str);
			compl_str[str_len - 1] = '\0';
			eof = true;
		}
		else
		{
			tmp = compl_str;
			ft_join_n_str(&compl_str, 3, tmp, new_line, "\n");
			if (ft_join_n_str(&compl_str, 3, tmp, new_line, "\n") == -1)
				return (printf("Error: joining strings\n"));
			free(tmp);
		}
		free(new_line);
	}
	printf("res child = $%s$\n", compl_str);
	if (write(fd[1], compl_str, str_len) == -1)
		return (printf("Error: writing to pipe\n"));
	if (close(fd[1]) == -1)
		return (printf("Error: closing pipe\n"));
	exit(0);
}
