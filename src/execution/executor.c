#include "minishell.h"

static int	executor_fork(t_main_data *data, t_pipefd *pipe_struct);
static int	executor_parent(pid_t pid, t_pipefd *pipe_struct);

int	executor(t_main_data *data)
{
	int			pipefd[2];
	t_pipefd	*pipe_struct;
	int			exit_code_pipe[2];

	pipe_handler(pipefd, "function \"executor\" main pipe");
	pipe_handler(exit_code_pipe, "function \"executor\" exit_code_pipe");
	pipe_struct = use_malloc(sizeof(t_pipefd), "function executor");
	if (!pipe_struct)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"executor\""});
	pipe_struct->pipefd = pipefd;
	pipe_struct->pipefd_exit_code = exit_code_pipe;
	executor_fork(data, pipe_struct);
	if (read_pipe(data, pipe_struct) == -1)
	{
		free(pipe_struct);
		pipe_struct = NULL;
		return (-1);
	}
	free(pipe_struct);
	return (0);
}

static int	executor_fork(t_main_data *data, t_pipefd *pipe_struct)
{
	pid_t	pid;
	int		ret;

	pid = fork_handler("function \"executor\"");
	if (pid < 0)
	{
		free(pipe_struct);
		pipe_struct = NULL;
		return (-1);
	}
	if (pid == 0)
	{
		ret = navigate_tree_forward(data, data->ast, pipe_struct);
		pipe_setting_exit_code(pipe_struct->pipefd_exit_code, true, &ret,
			"pipe exit code send");
		free(pipe_struct);
		pipe_struct = NULL;
		free_main_exit(data, 0);
		data = NULL;
		exit(EXIT_SUCCESS);
	}
	else
		executor_parent(pid, pipe_struct);
	return (0);
}

static int	executor_parent(pid_t pid, t_pipefd *pipe_struct)
{
	int	status;
	int	get_exit_code;

	waitpid(pid, &status, 0);
	pipe_setting_exit_code(pipe_struct->pipefd_exit_code, false, &get_exit_code,
		"function \"executor\" pipe");
	if (PRINT_DEBUG_1)
		printf("GET EXIT CODE: |%d|\n", get_exit_code);
	set_exit_code(get_exit_code);
	return (0);
}
