#include "minishell.h"

bool	str_equal_test(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

t_node_exec	*test_cmd_exec(char *command, char *flag, bool is_inbuilt)
{
	t_node_exec	*exec;
	char		**args1;

	exec = malloc_handler(sizeof(t_node_exec));
	exec->type = EXEC;
	exec->file_path = strdup(command);
	args1 = malloc_handler(3 * sizeof(char *));
	if ((str_equal_test(command, "cd") == false) &&
		(str_equal_test(command, "echo") == false))
	{
		args1[0] = strdup(command);
		if (flag == NULL)
			args1[1] = NULL;
		else
			args1[1] = strdup(flag);
		args1[2] = NULL;
	}
	else
	{
		args1[0] = strdup(flag);
		args1[1] = NULL;
		args1[2] = NULL;
	}
	exec->argv = args1;
	exec->env = malloc_handler(3 * sizeof(char *));
	exec->env[0] = ft_strdup("LANG=en_US.UTF-8");
	exec->env[1] = ft_strdup("PATH=/usr/bin");
	exec->env[2] = NULL;
	exec->is_inbuilt = is_inbuilt;
	return (exec);
}

t_node_pipe	*test_cmd_pipe(enum e_node_type type_left,
		enum e_node_type type_right, void *node_left, void *node_right)
{
	t_node_pipe	*pipe;

	pipe = malloc_handler(sizeof(t_node_pipe));
	pipe->type = PIPE;
	pipe->left_node = malloc_handler(sizeof(t_node));
	pipe->left_node->node_type = node_left;
	pipe->left_node->type = type_left;
	pipe->right_node = malloc_handler(sizeof(t_node));
	pipe->right_node->node_type = node_right;
	pipe->right_node->type = type_right;
	return (pipe);
}

t_node_redir	*test_cmd_redir(char *filename,
		enum e_open_mode mode, enum e_std_fd in_or_out,
		enum e_node_type child_typ, void *left_node)
{
	t_node_redir *redir;
	redir = malloc_handler(sizeof(t_node_redir));
	redir->type = REDIR;
	redir->filename = ft_strdup(filename);
	redir->mode = mode;
	redir->in_or_out = in_or_out;
	redir->left_node = malloc_handler(sizeof(t_node));
	redir->left_node->type = child_typ;
	redir->left_node->node_type = left_node;
	return (redir);
}