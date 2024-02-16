#include "minishell.h"

int	throw_error(int errno, char *program_part, char *failed_func,
		char *passed_args, char *add_info)
{
	printf("Error: %s\n", strerror(errno));
	printf("Program Part: %s\n", program_part);
	printf("Failed Func: %s\n", failed_func);
	printf("Func Args: %s\n", passed_args);
	printf("Add Info: %s\n", add_info);
}