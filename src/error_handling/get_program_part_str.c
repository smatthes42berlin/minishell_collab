#include "minishell.h"

char	*get_program_part_str(enum e_program_part program_part)
{
	if (program_part == EPART_MAIN)
		return ("MAIN");
	if (program_part == EPART_TOKENISER)
		return ("TOKENISER");
	if (program_part == EPART_EXPANDER)
		return ("EXPANDER");
	if (program_part == EPART_PARSER)
		return ("PARSER");
	if (program_part == EPART_EXECUTOR)
		return ("EXECUTOR");
	return (NULL);
}
