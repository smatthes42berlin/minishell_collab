#include "minishell.h"

bool	delimiter_entered(char *new_line, t_here_doc_info *hdoc_info)
{
	return (ft_strcmp(new_line, hdoc_info->delim) == 0);
}

bool	pressed_ctrl_d(char *new_line)
{
	return (!new_line);
}

bool	check_compl_str_empty(t_here_doc_info *hdoc_info)
{
	if (!hdoc_info->compl_str)
	{
		hdoc_info->compl_str = ft_strdup("");
		if (!hdoc_info->compl_str)
			exit(throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
					EFUNC_MALLOC, "hdoc child adding newline"}));
		hdoc_info->str_len = 0;
		return (true);
	}
	else
		hdoc_info->str_len = ft_strlen(hdoc_info->compl_str);
	return (false);
}
