# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:58:39 by smatthes          #+#    #+#              #
#    Updated: 2024/01/13 14:29:00 by smatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include Makefile_src

SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDESRCPATH) -I$(INCLUDETESTPATH)
NAME = libft.a
TARGET_EXTENSION=  out
LINK = cc
CC = cc

PATHPROJABS = /home/smatthes/42cursus/projects42/push_swap/
INCLUDESRCPATH = ./include/
INCLUDETESTPATH = ./includetest/
SUBFOLDERSRC = . ascii/ convert/ io/ s_lst/ dc_lst/ mem/ split/ str/ int_arr/ get_next_line/ printf/ str_arr/ math/ files/
BASEPATHSRC = ./src/
PATHSRC = $(patsubst %,$(BASEPATHSRC)%,$(SUBFOLDERSRC))
PATHBUILD = build/
PATHOBJ = build/

VPATH = $(PATHSRC)

OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(PATHOBJ)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
