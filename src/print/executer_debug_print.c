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
		if (txt == 7)
			printf("-------EXCE inbulilt FALSE--\n");
		if (txt == 8)
			printf("-------EXCE inbulilt TRUE--\n");
		if (txt == 10)
		{
			t_node_exec *exec_node = (t_node_exec *)param;
			print_exec_node(exec_node, 1);
		}
		if (txt == 11)
		{
			t_node *node_node = (t_node *)param;
			print_type(node_node); 
		}
				if (txt == 11)
		{
			t_node *node_node = (t_node *)param;
			print_type(node_node); 
		}		
		if (txt == 20)
		{
			char *str = (char *)param;
			printf("--Executer - End Jump to ADD given str : |%s|\n", str);
		}
		if (txt == 21)
		{
			char *str = (char *)param;
			printf("--Executer - End Jump to CLR given str : |%s|\n", str);
		}
		if (txt == 22)
		{
			char *str = (char *)param;
			printf("--Executer - End Jump to CD given str : |%s|\n", str);
		}
		
	}
	return ;
}