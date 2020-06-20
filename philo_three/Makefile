# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/18 15:43:32 by fernando          #+#    #+#              #
#    Updated: 2020/06/20 15:38:36 by fjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

CC = gcc

CFLAGS = -Wall -Wextra -Werror

THREADS = -lpthread

HEADER = philo_three.h

SRC = philo_three \
	utils \
	message \

FIL = $(addsuffix .c, $(addprefix , $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) $(CFLAGS) $(THREADS) -o $(NAME) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
