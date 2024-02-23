#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	int		pipefd[2];
	pid_t	cpid;
	pid_t	cpid2;

	pipe(pipefd);

	cpid = fork();
	if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		cpid2 = fork();
		if (cpid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(cpid2, NULL, 0);
			waitpid(cpid, NULL, 0);
			printf("DONE\n");
		}
	}
	return (EXIT_SUCCESS);
}
