#include "minishell.h"

void print_debugging_info_executer(int on_off, int txt, void *param)
{
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
		if (txt == 9)
			printf("----------BUILDIN chossen\n");
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
		if (txt == 23)
		{
			printf("--Buildin -- echo\n");
		}
		if (txt == 24)
		{
			printf("--Buildin -- pwd\n");
		}
		if (txt == 25)
		{
			printf("--Buildin -- cd\n");
		}
		if (txt == 26)
		{
			printf("--Buildin -- export\n");
		}
		if (txt == 27)
		{
			printf("--Buildin -- unset\n");
		}
		if (txt == 28)
		{
			printf("--Buildin -- env\n");
		}
		if (txt == 29)
		{
			printf("-----type Heredoc--\n");
		}
		if (txt == 30)
		{
			char *str = (char *)param;
			printf("--Executer - End Jump to EXIT-CODE given str : |%s|\n", str);
		}
	}
	return ;
}