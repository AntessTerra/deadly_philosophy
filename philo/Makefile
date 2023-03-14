# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 14:25:22 by jbartosi          #+#    #+#              #
#    Updated: 2023/03/14 14:30:02 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

THREADS = -pthread
CFLAGS = -Wall -Wextra -Werror

SRC = philosophers.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@cc -g -c $<

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(THREADS) -o $@ $^

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re:	fclean
	@make all

.PHONY: re, fclean, clean


