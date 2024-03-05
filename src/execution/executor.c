#include "minishell.h"

static int	executor_fork(t_main_data *data, t_pipefd *pipe_struct);
static int	executor_parent(pid_t pid, t_pipefd *pipe_struct);
// static	void	free_main(t_main_data *data);

// void	printAllPIDs(void)
// {
// 	DIR				*dir;
// 	struct dirent	*ent;
// 			char *p;

// 	// Versuche, das /proc Verzeichnis zu öffnen
// 	dir = opendir("/proc");
// 	if (dir != NULL)
// 	{
// 		// Lese Einträge im Verzeichnis
// 		while ((ent = readdir(dir)) != NULL)
// 		{
// 			// Überprüfe, ob der Verzeichnisname nur aus Zahlen besteht
// 			for (p = ent->d_name; *p; p++)
// 			{
// 				if (!isdigit(*p))
// 				{
// 					break ;
// 				}
// 			}
// 			if (!*p)
// 			{
// 				printf("%s\n", ent->d_name);
// 			}
// 		}
// 		// Schließe das Verzeichnis
// 		closedir(dir);
// 	}
// 	else
// 	{
// 		// Verzeichnis konnte nicht geöffnet werden
// 		perror("Fehler beim Öffnen von /proc");
// 	}
// }

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
	//printAllPIDs();

	printf("PID Main Process %d\n", getpid());
	executor_fork(data, pipe_struct);
	if (read_pipe(data, pipe_struct) == -1)
	{
		free_ast(data->ast);
		free(pipe_struct);
		return (-1);
	}
	free_ast(data->ast);
	free(pipe_struct);
	return (0);
}

static int	executor_fork(t_main_data *data, t_pipefd *pipe_struct)
{
	pid_t	pid;

	pid = fork_handler("function \"executor\"");
	if (pid < 0)
	{
		free(pipe_struct);
		free_main_exit(data, 0);
		return (-1);
	}
	if (pid == 0)
	{
		if (restore_default_signals(SIGQUIT + SIGINT))
			exit(errno);
		navigate_tree_forward(data, data->ast, pipe_struct);
		free(pipe_struct);
		free_main_exit(data, 0);
		printf("END OF MINI (CHILD) %d\n",  getpid());
	}
	else
		executor_parent(pid, pipe_struct);
	printf("END OF MINI (END) %d\n",  getpid());
	return (0);
}

static int	executor_parent(pid_t pid, t_pipefd *pipe_struct)
{
	int	status;
	int	res_wait_2;
	int	get_exit_code;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		res_wait_2 = WTERMSIG(status);
		if (WIFSIGNALED(status))
		{
			res_wait_2 = WTERMSIG(status);
			if (res_wait_2 == SIGINT)
				printf("\n");
			if (res_wait_2 == SIGQUIT)
				printf("Quit (core dumped)\n");
		}
	}
	pipe_setting_exit_code(pipe_struct->pipefd_exit_code, false, &get_exit_code,
		"function \"executor\" pipe");
	set_exit_code(get_exit_code);
	return (0);
}
