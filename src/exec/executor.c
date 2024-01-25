#include "minishell.h"

t_node	*example_selection(void)
{
	t_node	*ret;

	// ret = set_cmd_1();
	// ret = set_cmd_2();
	//ret = set_cmd_3();
	// ret = set_cmd_4();
	// ret = set_redir_in_1();
	//ret = set_redir_in_1_cmd_2();
	ret = set_redir_in_2_cmd_2();
	// ret = set_redir_out_1();
	return (ret);
}

void	executor(void)
{
	t_node	*example;

	example = example_selection();
	navigate_tree_forward(example);
}
