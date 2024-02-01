#include "minishell.h"

static int	free_compl_exit(char *compl_str, int code, char *msg);
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
		if (ft_strcmp(new_line, hdoc_info->delim) == 0)
			handle_end_reached(&compl_str, &str_len, &eof);
		else
			add_newline_to_compl_str(&compl_str, &new_line);
		free(new_line);
	}
	if (write(fd[1], compl_str, str_len + 1) == -1)
		return (free_compl_exit(compl_str, 2, "Error: writing to pipe"));
	if (close(fd[1]) == -1)
		return (free_compl_exit(compl_str, 3, "Error: closing pipe"));
	return (free_compl_exit(compl_str, 0, NULL));
}

static void	add_newline_to_compl_str(char **compl_str, char **new_line)
{
	char	*tmp;

	tmp = *compl_str;
	if (ft_join_n_str(compl_str, 3, tmp, *new_line, "\n") == -1)
	{
		free(*new_line);
		free(tmp);
		printf("Error: joining strings\n");
		exit(1);
	}
	free(tmp);
}

static void	handle_end_reached(char **compl_str, int *str_len, bool *eof)
{
	if (!*compl_str)
	{
		*compl_str = ft_strdup("");
		*str_len = 0;
	}
	else
		*str_len = ft_strlen(*compl_str);
	*eof = true;
}

static int	free_compl_exit(char *compl_str, int code, char *msg)
{
	free(compl_str);
	if (msg)
		printf("%s\n", msg);
	exit(code);
}
