# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 16:24:58 by ihhadjal          #+#    #+#              #
#    Updated: 2024/12/12 11:46:44 by ihhadjal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = parsing.c so_long.c parsing2.c floodfill.c
OBJS = ${SRCS:.c=.o}
NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
RM = rm -rf
LIBFT = ./libft
INCLUDES = -I/usr/include -Imlx -Iincludes
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

all : ${NAME}

${NAME}: ${OBJS}
	${MAKE} -C ./libft/
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ./libft/libft.a ${MLX_FLAGS}

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	${MAKE} clean -C ./libft/
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re