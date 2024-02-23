#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int	main(void)
{
	int		pipefd[2];
	char	*str[] = {"Dies ist ein Test", "Suchbegriff gefunden",
			"Ende der Nachrichten", NULL};

	pid_t pid1, pid2;
	char *grep_args[] = {"grep", "Suchbegriff", NULL};
		// Ersetze "Suchbegriff" durch deinen Suchbegriff
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{ // Erster Child-Prozess
		// Schließe Leseende im Child
		close(pipefd[0]);
		// Schreibe deine Strings in die Pipe, gefolgt von einem Zeilenumbruch
		for (int i = 0; str[i] != NULL; i++)
		{
			write(pipefd[1], str[i], strlen(str[i]));
			write(pipefd[1], "\n", 1);
				// Füge einen Zeilenumbruch nach jedem String hinzu
		}
		close(pipefd[1]); // Schließe das Schreibende der Pipe
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Parent-Prozess wartet auf das Ende des ersten Child-Prozesses
		waitpid(pid1, NULL, 0);
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid2 == 0)
		{ // Zweiter Child-Prozess für grep
			// Schließe Schreibende im zweiten Child
			close(pipefd[1]);
			// Leite das Leseende der Pipe auf STDIN um
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			// Führe grep aus
			execve("/bin/grep", grep_args, NULL);
			// Wenn execve fehlschlägt
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Schließe beide Enden der Pipe im Parent
			close(pipefd[0]);
			close(pipefd[1]);
			// Warte auf das Ende des grep-Prozesses
			waitpid(pid2, NULL, 0);
		}
	}
	return (EXIT_SUCCESS);
}
