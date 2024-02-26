#include "minishell.h"

static int	free_compl_exit(t_here_doc_info *hdoc_info, char *msg,
				enum e_failed_func failed_func, bool success);
static void	handle_end_reached(t_here_doc_info *hdoc_info, bool *eof);
static void	add_newline_to_compl_str(t_here_doc_info *hdoc_info,
				char **new_line);

int	child_read_hdoc(t_here_doc_info *hdoc_info, int fd[2])
{
	char	*new_line;
	bool	eof;

	eof = false;
	while (!eof)
	{
		new_line = readline(">");
		if (delimiter_entered(new_line, hdoc_info))
			handle_end_reached(hdoc_info, &eof);
		else if (pressed_ctrl_d(new_line))
			handle_eof_signaled(hdoc_info, &eof);
		else
			add_newline_to_compl_str(hdoc_info, &new_line);
		free(new_line);
	}
	if (write(fd[1], hdoc_info->compl_str, hdoc_info->str_len + 1) == -1)
		return (free_compl_exit(hdoc_info, "hdoc child writing to pipe",
				EFUNC_WRITE, 0));
	if (close(fd[1]) == -1)
		return (free_compl_exit(hdoc_info, "hdoc child closing pipe",
				EFUNC_CLOSE, 0));
	return (free_compl_exit(hdoc_info, NULL, EFUNC_FREE, 1));
}

int	handle_eof_signaled(t_here_doc_info *hdoc_info, bool *eof)
{
	printf("minishell: warning: here-document at line ");
	printf("%d ", hdoc_info->main_data->num_lines);
	printf("delimited by end-of-file (wanted ");
	printf("`%s')\n", hdoc_info->delim);
	check_compl_str_empty(hdoc_info);
	*eof = true;
	return (0);
}

static void	add_newline_to_compl_str(t_here_doc_info *hdoc_info,
										char **new_line)
{
	char	*tmp;

	tmp = hdoc_info->compl_str;
	if (ft_join_n_str(&(hdoc_info->compl_str), 3, tmp, *new_line, "\n") == -1)
	{
		free(*new_line);
		free(tmp);
		exit(throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_MALLOC, "hdoc child joining strings"}));
	}
	free(tmp);
}

static void	handle_end_reached(t_here_doc_info *hdoc_info, bool *eof)
{
	if (check_compl_str_empty(hdoc_info))
		;
	else
		hdoc_info->str_len = ft_strlen(hdoc_info->compl_str);
	*eof = true;
}

static int	free_compl_exit(t_here_doc_info *hdoc_info, char *msg,
		enum e_failed_func failed_func, bool success)
{
	free_heredoc_info_code(hdoc_info, 0);
	free_main_exit(hdoc_info->main_data, -1);
	if (success)
		exit(0);
	exit(throw_error_custom((t_error_ms){errno, EPART_TOKENISER, failed_func,
			msg}));
	return (0);
}
