#ifndef MINISHELL_EXPERIMENTAL_H
# define MINISHELL_EXPERIMENTAL_H

typedef struct s_token_state
{
	bool	inside_dq;
	bool	inside_sq;
	bool	inside_word;
	bool	inside_operator;
}			t_token_state;

#endif