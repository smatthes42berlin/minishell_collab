#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		systemstate = STATE_SIGINT;
		printf("\n");
		write(STDOUT_FILENO, "\n", 0);
		//write(STDOUT_FILENO, '\0', 1);
		rl_replace_line("", 1);
		rl_redisplay();
 //const char msg[] = "\nSIGINT empfangen, drücke nochmals Ctrl+C\ncli> ";
      //  write(STDOUT_FILENO, msg, sizeof(msg) - 1); // -1, um das Nullterminator-Zeichen nicht zu schreiben

		// printf("\nSIGINT empfangen, drücke nochmals Ctrl+C\n");
		// //exit(130);
		// write(STDOUT_FILENO, "\n", 1);
		return;
	}
	// if (sig == SIGQUIT)
	// {
	// 	signal(SIGQUIT, SIG_IGN);
	// 	systemstate = STATE_SIGQUIT;
	// 	printf("\nSIGINT empfangen, drücke nochmals Ctrl+\\\n");
	// }
	if (sig == 1000)
	{
		systemstate = STATE_EOF;
		printf("\nSIGINT empfangen, drücke nochmals Ctrl+D\n");
	}
}