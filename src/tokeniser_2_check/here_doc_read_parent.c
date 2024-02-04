#include "minishell.h"

int	parent_get_str_child(t_list_d **hdoc_op_token, int fd[2], int pid,
		t_here_doc_info *hdoc_info)
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
	if (res_wait)
		return (printf("Error: problem in heredoc child writing to pipe"));
	if (read_whole_file(fd[0], &res))
		return (printf("Error: reading from pipe"));
	if (close(fd[0]) == -1)
		return (printf("Error: closing pipe"));
	if (add_heredoc_str_token(hdoc_op_token, res, hdoc_info))
		return (printf("Error: problem manipulating linked list heredoc"));
	return (0);
}

int	add_heredoc_str_token(t_list_d **hdoc_op_token, char *res,
		t_here_doc_info *hdoc_info)
{
	t_list_d	*next_token;
	t_token		*next_token_val;
	char		*tmp;

	next_token = (*hdoc_op_token)->next;
	next_token_val = next_token->content;
	if (hdoc_info->quoted)
	{
		if (ft_join_n_str(&tmp, 3, "'", res, "'") == -1)
		{
			free(res);
			return (printf("Error: adding single quotes to heredoc\n"));
		}
		free(res);
		res = tmp;
	}
	free(next_token_val->value);
	next_token_val->value = res;
	next_token_val->type = T_HEREDOC;
	return (0);
}
