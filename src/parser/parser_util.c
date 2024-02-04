
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

int	append_to_last_redir(t_node *cur_root, t_node *new_node)
{
	t_node	*cur_node;

	if (cur_root->type == PIPE)
	{
		cur_node = cur_root->right_node;
		if (!cur_node)
		{
			cur_root->right_node = new_node;
			new_node->parent_node = cur_root;
			return (0);
		}
	}
	else
		cur_node = cur_root;
	printf("RRR: %s \n", cur_node->token_value);
	while (cur_node->left_node && !node_is_exec(cur_node))
	{
		cur_node = cur_node->left_node;
	}
	printf("TTT: %s \n", cur_node->token_value);
	if (node_is_exec(cur_node))
	{
		printf("SSS: %s \n", cur_node->token_value);
		printf("PARENT: %s \n", cur_node->parent_node->token_value);
		printf("new_node: %s \n", new_node->token_value);
		new_node->parent_node = cur_node->parent_node;
		new_node->left_node = cur_node;
		cur_node->parent_node->left_node = new_node;
		cur_node->parent_node = new_node;
		// new_node->parent_node->token_value = "1234\n";
		// new_node->token_value = "ddd\n";
		// cur_node->token_value = "ttt\n";
	}
	else
	{
		cur_node->left_node = new_node;
		new_node->parent_node = cur_node;
	}
	return (0);
}

int	set_exec_args_as_parsed(t_parse_info *parse_info)
{
	t_list_d	*lst;
	t_token		*token;

	lst = parse_info->next;
	token = lst->content;
	printf("toke val %s\n\n", token->value);
	while (lst && !token_is_pipe(token))
	{
		if (token_is_redir(token) || token_is_here_doc(token))
		{
			lst = lst->next;
			lst = lst->next;
			continue ;
		}
		else
		{
			token->parsed = true;
			lst = lst->next;
		}
		if (lst)
			token = lst->content;
	}
	return (0);
}
