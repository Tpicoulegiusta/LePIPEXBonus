# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 09:58:45 by tpicoule          #+#    #+#              #
#    Updated: 2023/02/03 11:40:28 by tpicoule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex_bonus
SOURCES		= pipex_utils_bonus.c \
			  pipex_utils_2_bonus.c \
			  pipex_bonus.c
OBJECTS		= ${SOURCES:.c=.o}
RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJECTS}

all:		${NAME}

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
