#include "minishell.h"

static int	free_compl_exit(char *compl_str, char *msg,
				enum e_failed_func failed_func, bool success);
static void	handle_end_reached(char **compl_str, int *str_len, bool *eof);
static void	add_newline_to_compl_str(char **compl_str, char **new_line);

int	child_read_hdoc(t_here_doc_info *hdoc_info, int fd[2])
{
	char	*compl_str;
	char	*new_line;
	bool	eof;
	int		str_len;

	eof = false;
	compl_str = NULL;
	while (!eof)
	{
		new_line = readline(">");
		if (delimiter_entered(new_line, hdoc_info))
			handle_end_reached(&compl_str, &str_len, &eof);
		else if (pressed_ctrl_d(new_line))
			handle_eof_signaled(hdoc_info, &eof, &compl_str, &str_len);
		else
			add_newline_to_compl_str(&compl_str, &new_line);
		free(new_line);
	}
	if (write(fd[1], compl_str, str_len + 1) == -1)
		return (free_compl_exit(compl_str, "hdoc child writing to pipe",
				EFUNC_WRITE, 0));
	if (close(fd[1]) == -1)
		return (free_compl_exit(compl_str, "hdoc child closing pipe",
				EFUNC_CLOSE, 0));
	return (free_compl_exit(compl_str, NULL, EFUNC_FREE, 1));
}

int	handle_eof_signaled(t_here_doc_info *hdoc_info, bool *eof, char **compl_str,
		int *str_len)
{
	printf("minishell: warning: here-document at line ");
	printf("%d", hdoc_info->main_data->num_lines);
	printf("delimited by end-of-file (wanted ");
	printf("`%s')\n", hdoc_info->delim);
	set_compl_str_empty(compl_str, str_len);
	*eof = true;
	return (0);
}

static void	add_newline_to_compl_str(char **compl_str, char **new_line)
{
	char	*tmp;

	tmp = *compl_str;
	if (ft_join_n_str(compl_str, 3, tmp, *new_line, "\n") == -1)
	{
		free(*new_line);
		free(tmp);
		exit(throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
					EFUNC_MALLOC, "hdoc child joining strings"}));
	}
	free(tmp);
}

static void	handle_end_reached(char **compl_str, int *str_len, bool *eof)
{
	if (!*compl_str)
		set_compl_str_empty(compl_str, str_len);
	else
		*str_len = ft_strlen(*compl_str);
	*eof = true;
}

static int	free_compl_exit(char *compl_str, char *msg,
		enum e_failed_func failed_func, bool success)
{
	free(compl_str);
	if (success)
		exit(0);
	exit(throw_error_custom((t_error_ms){errno, EPART_TOKENISER, failed_func,
				msg}));
	return (0);
}
