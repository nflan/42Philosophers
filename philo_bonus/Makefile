# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 11:05:20 by nflan             #+#    #+#              #
#    Updated: 2022/05/10 15:15:04 by nflan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main_bonus.c srcs/ft_tools_bonus.c srcs/ft_parse_bonus.c \
	   srcs/ft_finish_bonus.c srcs/ft_utils_bonus.c srcs/ft_do_it_bonus.c \
	   srcs/ft_philo_bonus.c

INC = include/philo_bonus.h

OBJS = ${SRCS:.c=.o}

NAME = philo_bonus

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

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
