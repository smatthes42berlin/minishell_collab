#include "minishell.h"

void print_debugging_info_executer(int on_off, int txt, void *param)
{
	if (param != NULL)
		printf("para == 0");

	if (on_off == 1)
	{
		if (txt == 1)
			printf("@@@@@@@@@@@@ Start Navigate @@@@@@@@@!\n");
		if (txt == 2)
			printf("@@@@@@@@@@@@ Ende Navigate @@@@@@@@@!\n");
        if (txt == 3)
			printf("--Navigate--\n");
        if (txt == 4)
			printf("-----type EXEC--\n");
        if (txt == 5)
			printf("-----type REDIR--\n");
        if (txt == 6)
			printf("-----type PIPE--\n");
	}
	return ;
}