# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:58:39 by smatthes          #+#    #+#              #
#    Updated: 2023/11/18 14:22:44 by smatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $^ -> all prerequisites with spaces in between
# $@ -> filename of the target of the rule
# $< ->  name of the first prerequisite
# $(info $(ADDHEADERLOC))


# -I Flag adds path where header files are searched during preprocessing
SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror $(INCLUDEFLAGS) 
NAME = pipex
LINK= cc
CC = cc

NAMELIBFT = libft.a
FOLDERLIBFT = ./libft/
PATHLIBFT = $(FOLDERLIBFT)$(NAMELIBFT)

INCLUDEPATH = ./include/ ./libft/include/
INCLUDEFLAGS = $(patsubst %,-I% ,$(INCLUDEPATH))
SUBFOLDERSRC = .
BASEPATHSRC = ./src/
PATHSRC = $(patsubst %,$(BASEPATHSRC)%,$(SUBFOLDERSRC))
PATHBUILD = build/
PATHOBJ = build/obj/

VPATH = $(PATHSRC) $(INCLUDEPATH)

SRC = 	main.c \
		process_main.c \
		process_cmd1.c \
		process_cmd2.c \
		utils.c \
		free.c \
		exit.c \
		handle_args.c
		
OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

.PHONY: all clean fclean re  

all: $(NAME)

$(NAME): $(PATHLIBFT) $(OBJ) 
	$(LINK) $(CFLAGS) -o $(NAME) $(OBJ) $(PATHLIBFT)

$(PATHOBJ)%.o: %.c pipex.h
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
