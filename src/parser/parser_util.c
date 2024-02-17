#include "minishell.h"

int	set_as_root(t_parse_info *parse_info, t_node *node)
{
	parse_info->root_node_ast = node;
	return (0);
}

int	check_new_root_node(t_parse_info *parse_info, t_node *new_node)
{
	if (!parse_info->root_node_ast)
	{
		parse_info->root_node_ast = new_node;
		return (1);
	}
	return (0);
}

int	set_n_token_as_parsed(int num, t_parse_info *parse_info)
{
	int			i;
	t_list_d	*lst;
	t_token		*token;

	lst = parse_info->next;
	i = 0;
	while (i < num && lst)
	{
		token = lst->content;
		token->parsed = true;
		lst = lst->next;
		i++;
	}
	return (0);
}

int	got_to_nth_next_token(int num, t_parse_info *parse_info)
{
	int	i;

	i = 0;
	while (i < num && parse_info->next)
	{
		parse_info->next = parse_info->next->next;
		i++;
	}
	return (0);
}
