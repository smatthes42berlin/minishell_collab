#include "minishell.h"

// ctrl + D -> EOF -> closes stdin pipe
// ctrl + \ -> QUIT -> SIGQUIT 3
// ctrl + C -> INTERUPT -> SIGINT 2

// in interactive mode
// ctrl + D -> exit shell
// ctrl + C -> newline
// ctrl + \ -> does nothing




// void	handle_ctrl_bs_sigquit(int sig)
// {
// 	printf("quit: %d!\n", sig);
// }

// void	handle_ctrl_c_sigint(int sig)
// {
// 	sig++;
// 	printf("interrupt ctr + c: %d!\n", sig);
// 	// rl_replace_line("", 0);
// 	printf("\n");
// 	// rl_on_new_line();
// 	// rl_redisplay();
// 	// set_exit_code(130);
// 	// rl_on_new_line();
// 	// rl_redisplay();
// }

// int	ignore_signal(int signal)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = SIG_IGN;
// 	sigaction(signal, &sa, NULL);
// 	return (0);
// }

// void	signal_main(void)
// {
// 	struct sigaction sa;
// 	struct sigaction old;

// 	sa.sa_handler = &handle_ctrl_bs_sigquit;
// 	sigaction(SIGINT, &sa, NULL);

// 	sa.sa_handler = &handle_ctrl_c_sigint;
// 	sigaction(SIGINT, &sa, &old);

// 	printf("ptr %p\n", old.sa_handler);

// 	// signal(SIGINT, SIG_IGN);
// 	// signal(SIGQUIT, SIG_IGN);

// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// }