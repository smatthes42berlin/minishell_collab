# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/14 09:56:29 by smatthes          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/01/20 09:30:40 by smatthes         ###   ########.fr        #
=======
#    Updated: 2024/01/19 15:10:11 by smatthes         ###   ########.fr        #
>>>>>>> 9d8782a (creation of token list workin 1.0)
#                                                                              #
# **************************************************************************** #

SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror $(INCLUDEFLAGS) 
NAME = minishell
LINK= cc
CC = cc

NAMELIBFT = libft.a
FOLDERLIBFT = ./libft/
PATHLIBFT = $(FOLDERLIBFT)$(NAMELIBFT)

INCLUDEPATH = ./include/ ./libft/include/
INCLUDEFLAGS = $(patsubst %,-I% ,$(INCLUDEPATH))
# if you created a new subfolder in the source dir, you gotta list it here as well, so c-files are found
SUBFOLDERSRC = . /tokeniser
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
		token_util_2.c \
		print_token_list.c
		
		
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
