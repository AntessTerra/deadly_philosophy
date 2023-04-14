# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 14:25:22 by jbartosi          #+#    #+#              #
#    Updated: 2023/04/14 13:22:13 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

THREADS = -pthread
CFLAGS = -Wall -Wextra -Werror

SRC = philosophers_bonus.c philosophers_utils_bonus.c routines_bonus.c
OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(SRC)
	@cc -g $(CFLAGS) $(THREADS) -o $@ $^

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re:	fclean
	@make all

.PHONY: re, fclean, clean


