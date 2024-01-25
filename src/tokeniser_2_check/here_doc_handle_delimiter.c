#include "minishell.h"

int	check_heredoc_delim(t_here_doc_info *hdoc_info)
{
	int	i;

	i = 0;
	while (hdoc_info->delim_raw[i])
	{
		if (is_squote(hdoc_info->delim_raw[i])
			|| is_dquote(hdoc_info->delim_raw[i]))
		{
			if (copy_unquoted_chars(hdoc_info, i))
				return (1);
			if (handle_quotes(hdoc_info, &i))
				return (2);
		}
		else
		{
			i++;
			hdoc_info->num_char_no_quote++;
		}
	}
	if (copy_unquoted_chars(hdoc_info, i))
		return (-1);
	return (0);
}



int	handle_quotes(t_here_doc_info *hdoc_info, int *i)
{
	hdoc_info->index_close_quote = has_closing_quote(&(hdoc_info->delim_raw[*i
				+ 1]), hdoc_info->delim_raw[*i]);
	if (hdoc_info->index_close_quote == -1)
		return (printf("Error: No closing quote found in heredoc!"));
	hdoc_info->quoted = true;
	if (ft_str_n_join_int(hdoc_info->delim, &(hdoc_info->delim_raw[*i + 1]),
			hdoc_info->index_close_quote + 1, &hdoc_info->tmp) == -1)
		return (printf("Error: Malloc when joining delim string!"));
	free(hdoc_info->delim);
	hdoc_info->delim = hdoc_info->tmp;
	hdoc_info->tmp = NULL;
	*i = *i + hdoc_info->index_close_quote + 2;
	return (0);
}

int	copy_unquoted_chars(t_here_doc_info *hdoc_info, int i)
{
	if (hdoc_info->num_char_no_quote == 0)
		return (0);
	if (ft_str_n_join_int(hdoc_info->delim, &(hdoc_info->delim_raw[i
				- hdoc_info->num_char_no_quote]), hdoc_info->num_char_no_quote
			+ 1, &hdoc_info->tmp) == -1)
		return (printf("Error: Malloc when joining delim string!"));
	free(hdoc_info->delim);
	hdoc_info->delim = hdoc_info->tmp;
	hdoc_info->tmp = NULL;
	hdoc_info->num_char_no_quote = 0;
	return (0);
}