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

INCLUDEPATH = ./include/ ./libft/include/
INCLUDEFLAGS = $(patsubst %,-I% ,$(INCLUDEPATH))
# if you created a new subfolder in the source dir, you gotta list it here as well, so c-files are found
SUBFOLDERSRC = . /tokeniser_1_create /tokeniser_2_check /env_vars /expander /parser /gen_util/
BASEPATHSRC = ./src/
PATHSRC = $(patsubst %,$(BASEPATHSRC)%,$(SUBFOLDERSRC))
PATHBUILD = build/
PATHOBJ = build/

# specifies the path, where the compiler will look for files (e.g. *.c, *.h files)
# that way, you dont have to specify full filepath when listing source files below
VPATH = $(PATHSRC) $(INCLUDEPATH)

# list all filenames (without path) here
SRC = 	main.c \
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
		expander_util.c \
		expander_expand_var.c \
		is_something_char.c \
		is_something_token.c \
		is_something_token_2.c \
		is_something_node.c \
		parser_util.c \
		parser_main.c \
		print_ast.c \
		parser_create_nodes.c \
		parser_add_nodes_ast.c

#parser_main.c
	

		
OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

.PHONY: all clean fclean re  

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

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PRECIOUS: $(PATHOBJ)%.o
