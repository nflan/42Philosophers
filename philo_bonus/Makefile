# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 11:05:20 by nflan             #+#    #+#              #
#    Updated: 2022/04/19 11:51:36 by nflan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main_bonus.c srcs/ft_tools_bonus.c srcs/ft_parse_bonus.c

INC = include/philo_bonus.h

OBJS = ${SRCS:.c=.o}

NAME = philo_bonus

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

bonus:	${NAME}

$(NAME):	${OBJS} ${INC}
	${CC} ${CFLAGS} -pthread ${OBJS} -I ${INC} -o ${NAME}

$(OBJS):	${INC}

clean:
	${RM} ${OBJS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
