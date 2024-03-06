# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_submit                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:58:39 by smatthes          #+#    #+#              #
#    Updated: 2023/06/26 15:07:16 by smatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $^ -> all prerequisites with spaces in between
# $@ -> filename of the target of the rule
# $< ->  name of the first prerequisite

include Makefile_src

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

OBJS = $(SRC:.c=.o)

.PHONY: all clean fclean re main

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all