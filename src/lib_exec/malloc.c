#include "minishell.h"

/**
 * @brief Using the funktion for safe malloc
 * 
 * @param bytes 
 * @return void* 
 */
void	*malloc_handler(size_t bytes)
{
	void    *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_code_handler(errno, "ERR-malloc", " ", " ");
	return (ret);
}