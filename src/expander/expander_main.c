#include "minishell.h"


// here_doc
// write full string to pipe
// save fd of specific pipe in token list
// dup2 the stdin of the cmd uisng the heredoc to this pipe
// here_doc basically acts as a redirect not for stdin to the heredoc buffer

int	expand(t_main_data *main_data)
{
    // loop through token list
    // if operator, continue
    // check token value
    // only dont expand when in single quotes
    // look for ?
    // get full name of variable
    // ends at whitespaces, quotes, stringends, and other charcters not allowed in var names like ?.{} etc
    // check for $character
	printf("EXPANDING LIKE THE UNIVERSE! %p\n\n\n", main_data);
	return (0);
}
