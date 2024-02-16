#include "minishell.h"

static int	go_to_last_node(t_node **cur_node);
static int	append_before_exec(t_parse_info *parse_info, t_node *cur_node,
				t_node *new_node);
static int	append_after_last_redir(t_node *cur_node,
				t_node *new_node);
static bool	handle_cur_pipe_root(t_node **cur_node,
				t_node *new_node);

int	append_to_last_redir(t_parse_info *parse_info, t_node *new_node)
{
	t_node	*cur_node;

	cur_node = parse_info->root_node_ast;
	if (handle_cur_pipe_root(&cur_node, new_node))
		return (0);
	go_to_last_node(&cur_node);
	if (node_is_exec(cur_node))
		append_before_exec(parse_info, cur_node, new_node);
	else
		append_after_last_redir(cur_node, new_node);
	return (0);
}

static int	go_to_last_node(t_node **cur_node)
{
	while ((*cur_node)->left_node && !node_is_exec(*cur_node))
	{
		*cur_node = (*cur_node)->left_node;
	}
	return (0);
}

static int	append_before_exec(t_parse_info *parse_info, t_node *cur_node,
		t_node *new_node)
{
	new_node->parent_node = cur_node->parent_node;
	new_node->left_node = cur_node;
	if (cur_node->parent_node)
	{
		if (cur_node->parent_node->type == PIPE)
			cur_node->parent_node->right_node = new_node;
		else
			cur_node->parent_node->left_node = new_node;
	}
	else
		set_as_root(parse_info, new_node);
	cur_node->parent_node = new_node;
	return (0);
}

static int	append_after_last_redir(t_node *cur_node,
									t_node *new_node)
{
	cur_node->left_node = new_node;
	new_node->parent_node = cur_node;
	return (0);
}

static bool	handle_cur_pipe_root(t_node **cur_node,
									t_node *new_node)
{
	t_node	*cur_root;

	cur_root = *cur_node;
	if (cur_root->type == PIPE)
	{
		*cur_node = cur_root->right_node;
		if (!*cur_node)
		{
			cur_root->right_node = new_node;
			new_node->parent_node = cur_root;
			return (1);
		}
	}
	return (0);
}
