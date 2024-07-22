# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samartin <samartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 15:15:33 by samartin          #+#    #+#              #
#    Updated: 2023/10/24 15:31:02 by samartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftprintf.a
CC		:= gcc
AR		:= ar -crs
SRC		:= ft_printf.c ft_printf_alpha_utils.c ft_printf_num_utils.c
OBJ		:= ${SRC:.c=.o}
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -rf

all: ${NAME}

${NAME}: ${OBJ}
	${AR} ${NAME} $^

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re bonus