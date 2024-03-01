#include "minishell.h"

static void	print_debugging_info_executer_1(int on_off, int txt, void *param);
static void	print_debugging_info_executer_2(int on_off, int txt, void *param);
static void	print_debugging_info_executer_3(int on_off, int txt);

void	print_debugging_info_executer(int on_off, int txt, void *param)
{
	if (on_off == 1)
	{
		if (txt == 1)
			printf("@@@@@@@@@@@@ Start Navigate @@@@@@@@@!\n");
		else if (txt == 2)
			printf("@@@@@@@@@@@@ Ende Navigate @@@@@@@@@!\n");
		else if (txt == 3)
			printf("--Navigate--\n");
		else if (txt == 4)
			printf("-----type EXEC--\n");
		else if (txt == 5)
			printf("-----type REDIR--\n");
		else if (txt == 6)
			printf("-----type PIPE--\n");
		else if (txt == 7)
			printf("-------EXCE inbulilt FALSE--\n");
		else if (txt == 8)
			printf("-------EXCE inbulilt TRUE--\n");
		else if (txt == 9)
			printf("----------BUILDIN chossen\n");
		else 
			print_debugging_info_executer_1(on_off, txt, param);
	}
	return ;
}

static void	print_debugging_info_executer_1(int on_off, int txt, void *param)
{
	t_node_exec	*exec_node;
	t_node		*node_node;
	char		*str;

	if (on_off == 1)
	{
		if (txt == 10)
		{
			exec_node = (t_node_exec *)param;
			print_exec_node(exec_node, 1);
		}
		else if (txt == 11)
		{
			node_node = (t_node *)param;
			print_type(node_node); 
		}
		else if (txt == 20)
		{
			str = (char *)param;
			printf("--Executer - End Jump to ADD given str : |%s|\n", str);
		}
		else 
			print_debugging_info_executer_2(on_off, txt, param);
	}
	return ;
}

static void	print_debugging_info_executer_2(int on_off, int txt, void *param)
{
	char		*str;

	if (on_off == 1)
	{
		if (txt == 21)
		{
			str = (char *)param;
			printf("--Executer - End Jump to CLR given str : |%s|\n", str);
		}
		else if (txt == 22)
		{
			str = (char *)param;
			printf("--Executer - End Jump to CD given str : |%s|\n", str);
		}
		else if (txt == 30)
		{
			str = (char *)param;
			printf("--Executer - End Jump to EXIT-CODE given str : |%s|\n", str);
		}
		else 
			print_debugging_info_executer_3(on_off, txt);
	}
	return ;
}

static void	print_debugging_info_executer_3(int on_off, int txt)
{
	if (on_off == 1)
	{
		if (txt == 23)
			printf("--Buildin -- echo\n");
		else if (txt == 24)
			printf("--Buildin -- pwd\n");
		else if (txt == 25)
			printf("--Buildin -- cd\n");
		else if (txt == 26)
			printf("--Buildin -- export\n");
		else if (txt == 27)
			printf("--Buildin -- unset\n");
		else if (txt == 28)
			printf("--Buildin -- env\n");
		else if (txt == 29)
			printf("-----type Heredoc--\n");
		else if (txt == 31)
			printf("--Buildin -- exit\n");
	}
	return ;
}
