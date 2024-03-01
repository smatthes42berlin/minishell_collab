#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	char	*program;
		char *argv[] = {program, NULL};
		int status;

	pid = fork();
	if (pid == 0)
	{
		// Kindprozess
		program = "nichtexistentesprogramm";
		// Überprüfen, ob das Programm existiert
		if (access(program, F_OK) != 0)
		{
			fprintf(stderr, "%s: command not found\n", program);
			exit(127); // Verwenden von Exit-Code 127 für "command not found"
		}
		// Überprüfen, ob das Programm ausführbar ist
		if (access(program, X_OK) != 0)
		{
			fprintf(stderr, "%s: permission denied\n", program);
			exit(126);
				// Optional: Verwenden von Exit-Code 126 für "permission denied"
		}
		execve(argv[0], argv, NULL);
		// Wenn execve zurückkehrt, ist ein Fehler aufgetreten
		fprintf(stderr, "Fehler beim Ausführen von %s: %s\n", program,
			strerror(errno));
		exit(EXIT_FAILURE);
			// Hier könnte ein spezifischer Exit-Code verwendet werden,
			//falls gewünscht
	}
	else if (pid > 0)
	{
		// Elternprozess
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			printf("Kindprozess beendet mit Status %d\n", WEXITSTATUS(status));
		}
	}
	else
	{
		// Fehler beim Forken
		fprintf(stderr, "Fork fehlgeschlagen\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
