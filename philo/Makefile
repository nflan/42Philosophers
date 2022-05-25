# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 15:05:20 by nflan             #+#    #+#              #
#    Updated: 2022/05/25 11:58:00 by nflan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/ft_tools.c srcs/ft_parse.c srcs/ft_philo.c \
	   srcs/ft_finish.c srcs/ft_init.c srcs/ft_utils.c srcs/ft_actions.c

INC = include/philo.h

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

$(NAME):	${OBJS} ${INC}
	${CC} ${CFLAGS} -pthread ${OBJS} -I ${INC} -o ${NAME}

$(OBJS):	${INC}

clean:
	${RM} ${OBJS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
