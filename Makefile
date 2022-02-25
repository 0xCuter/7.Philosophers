# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scuter <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 02:05:59 by scuter            #+#    #+#              #
#    Updated: 2022/02/25 03:21:08 by scuter           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

INC		=	includes/philo.h

SRC		=	srcs/main.c\
			srcs/utils.c\
			srcs/init.c\
			srcs/end.c\
			srcs/routine.c\
			srcs/actions.c\

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -pthread

OBJS	=	$(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
