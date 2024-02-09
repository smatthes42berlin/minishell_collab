
include Makefile_src

SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDESRCPATH)
NAME = libft.a
TARGET_EXTENSION=  out
LINK = cc
CC = cc

INCLUDESRCPATH = ./include/
SUBFOLDERSRC = . ascii/ convert/ io/ s_lst/ dc_lst/ d_lst/ mem/ split/ str/ int_arr/ get_next_line/ printf/ str_arr/ math/ files/ free/
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
