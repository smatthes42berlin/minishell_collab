#include "minishell.h"

char	*build_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		error_code_handler(errno, "ERR-getcwd", "", "");
	}
	// printf("Current directory: %s\n", cwd);
	//   write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	//   write(STDOUT_FILENO, "\n", 1);
	return (cwd);
	// free(cwd);
}

// -------------------- Test function ----------------------------------------

t_node	*set_pwd_allone(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("pwd", "pwd", NULL, true), ret->type = EXEC;
	return (ret);
}

// double command exeample "cmd | cmd"
t_node	*set_pwd_beginn_1(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, EXEC, test_cmd_exec("pwd",
				"pwd", NULL, true), test_cmd_exec("ls", "/bin/grep", "home",
				false));
	ret->type = PIPE;
	return (ret);
}

t_node	*set_pwd_begin_2(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, EXEC, test_cmd_exec("pwd",
				"pwd", NULL, true), test_cmd_exec("ls", "/bin/ls", "-l",
				false));
	ret->type = PIPE;
	return (ret);
}

t_node	*set_pwd_end(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, EXEC, test_cmd_exec("ls",
				"/bin/ls", "-l", false), test_cmd_exec("pwd", "pwd", NULL,
				true));
	ret->type = PIPE;
	return (ret);
}

t_node	*set_pwd_redir_out(void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_redir("Redir", "out", FILE_ONLY_WRITE_APPEND,
			STDOUT, EXEC, test_cmd_exec("pwd", "pwd", NULL, true));
	ret->type = REDIR;
	return (ret);
}