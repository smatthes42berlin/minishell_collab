SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror $(INCLUDEFLAGS)
# CFLAGS = -Wall -Wextra -Werror -fsanitize=leak  $(INCLUDEFLAGS) 
# CFLAGS = -Wall -Wextra -Werror fsanitize=addressmak  $(INCLUDEFLAGS) 
NAME = minishell
LINK= cc
CC = cc

NAMELIBFT = libft.a
FOLDERLIBFT = ./libft/
PATHLIBFT = $(FOLDERLIBFT)$(NAMELIBFT)

INCLUDEPATH = ./include/ ./libft/include/ ./libft/
INCLUDEFLAGS = $(patsubst %,-I% ,$(INCLUDEPATH))
# if you created a new subfolder in the source dir, you gotta list it here as well, so c-files are found
SUBFOLDERSRC = . /tokeniser_1_create /tokeniser_2_check /env_vars /expander /parser /execution /lib_exec /error_handling /builtins /gen_util /print /signals
BASEPATHSRC = ./src/
PATHSRC = $(patsubst %,$(BASEPATHSRC)%,$(SUBFOLDERSRC))
PATHBUILD = build/
PATHOBJ = build/

# create build folder
$(shell if [ ! -d $(PATHBUILD) ]; then \
    mkdir -p $(PATHBUILD); \
fi)

# specifies the path, where the compiler will look for files (e.g. *.c, *.h files)
# that way, you dont have to specify full filepath when listing source files below
VPATH = $(PATHSRC) $(INCLUDEPATH)

# list all filenames (without path) here
SRC = 	main.c \
		main_util.c \
		main_util_2.c \
		build_cd.c \
		build_cd_utiles.c \
		build_pwd.c \
		build_echo.c \
		build_export.c \
		build_exit.c \
		build_exit_utiles.c \
		builld_unset.c \
		build_env.c \
		choose_builtin.c \
		build_utiles.c \
		access.c \
		executor.c \
		executor_env_set.c \
		executer_read_pipe.c \
		utiles_execute.c \
		free_ast.c \
		exec_type_exec.c \
		exec_type_pipe.c \
		exec_type_pipe_utiles.c \
		exec_type_redir.c \
		exec_type_heredoc.c \
		tree_navigation.c \
		execve.c \
		exec_type_exec_null.c \
		malloc_handler.c \
		utiles_libft.c \
		fork_process_state.c \
		pipe.c \
		pipe_utiles.c \
		tokenise_main.c \
		append_token.c \
		identify_token.c \
		create_token.c \
		token_util.c \
		print_token_list.c \
		token_identify_operator.c \
		token_get.c \
		check_syntax_n_heredoc.c \
		check_syntax.c \
		check_last_node_exec.c \
		check_last_node_redir.c \
		here_doc_main.c \
		here_doc_handle_delimiter.c \
		here_doc_read.c \
		here_doc_read_parent.c \
		here_doc_read_child.c \
		tokenise_free.c \
		here_doc_remove_here_doc_token.c \
		env_init.c \
		env_del_var.c \
		env_print.c \
		env_set_var.c \
		env_get_var.c \
		expander_main.c \
		expander_check_expansion.c \
		expander_remove_empty_token.c \
		expander_util.c \
		expander_expand_var.c \
		expander_expand_var_fixed.c \
		expander_tilde.c \
		is_something_char.c \
		is_something_token.c \
		is_something_token_2.c \
		is_something_node.c \
		parser_util.c \
		parser_main.c \
		print_ast.c \
		parser_add_nodes_ast.c \
		parser_append_to_last_redir.c \
		check_syntax_util.c \
		parser_change_form_ast.c \
		parser_create_node_exec.c \
		parser_create_node_exec_2.c \
		parser_create_node_exec_util.c \
		parser_create_node_hdoc.c \
		parser_create_node_pipe.c \
		parser_create_node_redir.c \
		parser_create_node_util.c \
		parser_set_last_node.c \
		print_type.c \
		print_redir_node.c \
		print_hdoc_node.c \
		print_exec_node.c \
		print_pipe_node.c \
		get_program_part_str.c \
		get_failed_func_str.c \
		throw_error.c \
		here_doc_read_child_util.c \
		set_exit_code.c \
		ign_or_def_signals.c \
		signals_interactive.c \
		set_signal.c \
		set_program_name.c \
		print_debug.c \
		print_node_ast.c \
		get_exit_code.c

#parser_main.c
	

		
OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

.PHONY: all clean fclean re fcleanall reall leaks

all: $(NAME)

$(NAME): $(PATHLIBFT) $(OBJ)
	$(LINK) $(CFLAGS) -o $(NAME) $(OBJ) $(PATHLIBFT) -lreadline

$(PATHOBJ)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PATHLIBFT): 
	make -C $(FOLDERLIBFT)

clean:
	make -C $(FOLDERLIBFT) clean
	$(RM) $(OBJ)

fcleanall: clean
	make -C libft fclean
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

leaks:
	@echo -e "\n\n"
	@echo "Please copy/create supression file first: 'readline.supp' "
	@echo -e "\n\n"
	@make
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

reall: fcleanall all

re: fclean all

.PRECIOUS: $(PATHOBJ)%.o
