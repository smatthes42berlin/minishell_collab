#include "minishell.h"

static int	child_1(int pid_2);
static int	child_2(void);
static int	parent(int pid_1);

int	main(void)
{
	int	pid_1;
	int	pid_2;

	pid_1 = -1;
	pid_2 = -1;
	pid_1 = fork();
	ignore_signals(SIGINT + SIGQUIT);
	if (pid_1 == 0)
		pid_2 = fork();
	if (pid_1)
		parent(pid_1);
	else if (pid_2)
		child_1(pid_2);
	else
		child_2();
	return (0);
}

void	fucn(int signum)
{
	signum++;
	exit(signum);
}

static int	child_1(int pid_2)
{
	int	res_wait;
	int	status;

	res_wait = waitpid(pid_2, &status, 0);
	if (WIFEXITED(status))
	{
		printf("child 2 exited\n");
		res_wait = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		printf("child 2 signaled\n");
		res_wait = WTERMSIG(status);
	}
	printf("1\n");
	pid_2++;
	return (0);
}
static int	child_2(void)
{
	set_signal(SIGINT, fucn);
	while (1)
	{
		continue ;
	}
	return (0);
}
static int	parent(int pid_1)
{
	int	res_wait;
	int	status;

	res_wait = waitpid(pid_1, &status, 0);
	if (WIFEXITED(status))
	{
		printf("child 1 exited\n");
		res_wait = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		printf("child 1 signaled\n");
		res_wait = WTERMSIG(status);
	}
	pid_1++;
	wait(NULL);
	printf("2\n");
	return (0);
}

int	reset_main_data(t_main_data *main_data)
{
	main_data->ast = NULL;
	main_data->cli_input = NULL;
	main_data->env_vars = NULL;
	main_data->token_list = NULL;
	return (0);
}

t_main_data	*get_main_data(void)
{
	static t_main_data	data = {NULL, NULL, NULL, NULL, 0};

	return (&data);
}
