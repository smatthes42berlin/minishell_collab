
#include "minishell.h"

// check token type
// word -> create exec node get all next words as arguments
// operator -> create pipe or redirect node
// heredoc -> create heredoc node, write content to pipe and get pipe fd
//

int	parse(t_main_data *main_data)
{
	int				create_sucess;
	t_parse_info	parse_info;

	parse_info.next = main_data->token_list;
	parse_info.prev_node = NULL;
	parse_info.pre_prev_node = NULL;
	parse_info.root_node_ast = NULL;
	while (parse_info.next)
	{
		create_sucess = false;
		parse_info.cur_token = parse_info.next->content;
		// printf("$%s$\n", parse_info.cur_token->value);
		printf("KK: %s \n\n", parse_info.cur_token->value);
		if (parse_info.cur_token->parsed)
		{
			printf("PP: %s \n\n", parse_info.cur_token->value);
			got_to_nth_next_token(1, &parse_info);
			create_sucess = 0;
		}
		else if (token_is_redir(parse_info.cur_token))
			create_sucess = create_redir_node(&parse_info);
		else if (token_is_here_doc(parse_info.cur_token))
			create_sucess = create_hdoc_node(&parse_info);
		else if (token_is_pipe(parse_info.cur_token))
			create_sucess = create_pipe_node(&parse_info);
		else if (token_is_word(parse_info.cur_token))
			create_sucess = create_exec_node(&parse_info);
		else
			return (printf("Error: token type not recognised during parsing"));
		if (create_sucess)
		{
			// here function to free current ast needed
			return (1);
		}
	}
	print_ast(parse_info.root_node_ast, 0);
	return (0);
}

int	create_redir_node(t_parse_info *parse_info)
{
	t_node_redir	*redir_node;

	redir_node = malloc(sizeof(t_node_redir));
	if (!redir_node)
		return (printf("Error: Allocating memory for pipe\n"));
	redir_node->type = REDIR;
	redir_node->left_node = NULL;
	redir_node->right_node = NULL;
	redir_node->token_value = parse_info->cur_token->value;
	if (add_redir_ast(parse_info, redir_node))
		return (1);
	set_n_token_as_parsed(2, parse_info);
	return (0);
}

int	create_hdoc_node(t_parse_info *parse_info)
{
	t_node_heredoc	*hdoc_node;

	hdoc_node = malloc(sizeof(t_node_heredoc));
	if (!hdoc_node)
		return (printf("Error: Allocating memory for pipe\n"));
	hdoc_node->type = HEREDOC;
	hdoc_node->left_node = NULL;
	hdoc_node->right_node = NULL;
	hdoc_node->token_value = parse_info->cur_token->value;
	if (add_hdoc_ast(parse_info, hdoc_node))
		return (1);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}

int	create_pipe_node(t_parse_info *parse_info)
{
	t_node_pipe	*pipe_node;

	pipe_node = malloc(sizeof(t_node_pipe));
	if (!pipe_node)
		return (printf("Error: Allocating memory for pipe\n"));
	pipe_node->type = PIPE;
	pipe_node->left_node = NULL;
	pipe_node->right_node = NULL;
	pipe_node->token_value = parse_info->cur_token->value;
	if (add_pipe_ast(parse_info, pipe_node))
		return (1);
	set_n_token_as_parsed(1, parse_info);
	return (0);
}

int	create_exec_node(t_parse_info *parse_info)
{
	t_node_exec	*exec_node;

	exec_node = malloc(sizeof(t_node_exec));
	if (!exec_node)
		return (printf("Error: Allocating memory for pipe\n"));
	exec_node->type = EXEC;
	exec_node->left_node = NULL;
	exec_node->right_node = NULL;
	exec_node->token_value = parse_info->cur_token->value;
	if (add_exec_ast(parse_info, exec_node))
		return (1);
	set_exec_args_as_parsed(parse_info);
	return (0);
}

int	add_exec_ast(t_parse_info *parse_info, t_node_exec *new_node)
{
	t_node	*new_node_gen;

	new_node_gen = (t_node *)new_node;
	if (check_new_root_node(parse_info, new_node_gen))
		return (0);
	else if (node_is_pipe(parse_info->prev_node))
	{
		if (pipe_node_left_defined((t_node_pipe *)(parse_info->prev_node)))
			((t_node_pipe *)(parse_info->prev_node))->right_node = new_node_gen;
		else
			((t_node_pipe *)(parse_info->prev_node))->left_node = new_node_gen;
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else if (node_is_redir(parse_info->prev_node))
		((t_node_redir *)parse_info->prev_node)->left_node = new_node_gen;
	else if (node_is_hdoc(parse_info->prev_node))
		((t_node_heredoc *)parse_info->prev_node)->left_node = new_node_gen;
	else
		return (printf("Error: Case not handled for add exec node ast\n"));
	return (0);
}

int	add_redir_ast(t_parse_info *parse_info, t_node_redir *new_node)
{
	t_node	*new_node_gen;

	new_node_gen = (t_node *)new_node;
	if (check_new_root_node(parse_info, new_node_gen))
		// printf("PRE_PREV = %p \n\n", parse_info->pre_prev_node);
		return (0);
	else if (node_is_pipe(parse_info->prev_node))
	{
		if (pipe_node_left_defined((t_node_pipe *)(parse_info->prev_node)))
			((t_node_pipe *)(parse_info->prev_node))->right_node = new_node_gen;
		else
			((t_node_pipe *)(parse_info->prev_node))->left_node = new_node_gen;
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else if (node_is_exec(parse_info->prev_node))
	{
		new_node->left_node = parse_info->prev_node;
		if (node_is_pipe(parse_info->pre_prev_node))
			parse_info->pre_prev_node->right_node = new_node_gen;
		else
			set_as_root(parse_info, new_node_gen);
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else if (node_is_redir(parse_info->prev_node))
	{
		new_node->left_node = ((t_node_redir *)parse_info->prev_node)->left_node;
		((t_node_redir *)parse_info->prev_node)->left_node = new_node_gen;
	}
	else if (node_is_hdoc(parse_info->prev_node))
	{
		new_node->left_node = ((t_node_heredoc *)parse_info->prev_node)->left_node;
		((t_node_heredoc *)parse_info->prev_node)->left_node = new_node_gen;
	}
	else
		return (printf("Error: Case not handled for add redir node ast\n"));
	return (0);
}

int	add_hdoc_ast(t_parse_info *parse_info, t_node_heredoc *new_node)
{
	t_node	*new_node_gen;

	new_node_gen = (t_node *)new_node;
	;
	if (check_new_root_node(parse_info, new_node_gen))
		return (0);
	else if (node_is_pipe(parse_info->prev_node))
	{
		if (pipe_node_left_defined((t_node_pipe *)(parse_info->prev_node)))
			((t_node_pipe *)(parse_info->prev_node))->right_node = new_node_gen;
		else
			((t_node_pipe *)(parse_info->prev_node))->left_node = new_node_gen;
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else if (node_is_exec(parse_info->prev_node))
	{
		new_node->left_node = parse_info->prev_node;
		if (node_is_pipe(parse_info->pre_prev_node))
			parse_info->pre_prev_node->right_node = new_node_gen;
		else
			set_as_root(parse_info, new_node_gen);
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else if (node_is_redir(parse_info->prev_node))
	{
		new_node->left_node = ((t_node_redir *)parse_info->prev_node)->left_node;
		((t_node_redir *)parse_info->prev_node)->left_node = new_node_gen;
	}
	else if (node_is_hdoc(parse_info->prev_node))
	{
		new_node->left_node = ((t_node_heredoc *)parse_info->prev_node)->left_node;
		((t_node_heredoc *)parse_info->prev_node)->left_node = new_node_gen;
	}
	else
		return (printf("Error: Case not handled for add hdoc node ast\n"));
	return (0);
}

int	add_pipe_ast(t_parse_info *parse_info, t_node_pipe *new_node)
{
	t_node	*new_node_gen;

	new_node_gen = (t_node *)new_node;
	if (check_new_root_node(parse_info, new_node_gen))
		return (0);
	if (node_is_exec(parse_info->prev_node))
	{
		new_node->left_node = parse_info->prev_node;
		if (node_is_pipe(parse_info->pre_prev_node))
			((t_node_pipe *)(parse_info->pre_prev_node))->right_node = new_node_gen;
		else
			set_as_root(parse_info, new_node_gen);
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else if (node_is_redir(parse_info->prev_node)
			|| node_is_hdoc(parse_info->prev_node))
	{
		printf("xxx\n\n");
		new_node->left_node = parse_info->prev_node;
		if (node_is_pipe(parse_info->pre_prev_node))
			((t_node_pipe *)(parse_info->pre_prev_node))->right_node = new_node_gen;
		else
			set_as_root(parse_info, new_node_gen);
		adjust_prev_nodes_ast(parse_info, new_node_gen);
	}
	else
		return (printf("Error: Case not handled for add pipe node ast\n"));
	return (0);
}

int	set_exec_args_as_parsed(t_parse_info *parse_info)
{
	t_list_d	*lst;
	t_token		*token;

	lst = parse_info->next;
	while (lst && !token_is_pipe(token))
	{
		token = lst->content;
		// printf("HERE: %s\n\n", token->value);
		if (token_is_redir(token))
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
	}
	return (0);
}

// heredoc
// allocate memory
// set node type
// create subprocess and write to pipe in subprocess
// set read filedescriptor

// pipe
// allocate memory
// set node type

// command
// alocate memory
// set type
// set name exec
// check if it is inbuilt
// check if exec is found
// set filepath
// get all next tokens as args
// set environment pointer to our environment

// redirect
// alocate memory
// redirection input
// redirection output
// append or overwrite
// check, if file exists
// set mode
// set type
// write filename
// set childnode
// append to ast
