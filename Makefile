# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mykman <mykman@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/08 00:02:10 by mykman            #+#    #+#              #
#    Updated: 2022/08/07 17:53:53 by mykman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC				=	@gcc
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address

RED				:=	\033[38;5;9m
GREEN			:=	\033[38;5;10m
BLUE			:= 	\033[38;5;14m
YELLOW			:=	\033[38;5;226m
RESET			:=	\033[38;5;7m
PREFIX			=	[${YELLOW}${NAME}${RESET}]\t

# Variables
NAME			=	minitalk
CLIENT			=	client
SERVER			=	server
LIBFT_FOLDER	=	Libft/
LIBFT_NAME		=	libft.a
MAKE_LIBFT		=	@make -s -C ${LIBFT_FOLDER}

# Files
INCLUDES		=	-I./includes \
					-I./${LIBFT_FOLDER}/includes/ft_printf \
					-I./${LIBFT_FOLDER}/includes/general_functions
SRCS			=	minitalk.c
SRCS_CLIENT		=	client.c
SRCS_SERVER		=	server.c

OBJS			=	$(addprefix srcs/, ${SRCS:.c=.o})
OBJS_CLIENT		=	$(addprefix srcs/, ${SRCS_CLIENT:.c=.o})
OBJS_SERVER		=	$(addprefix srcs/, ${SRCS_SERVER:.c=.o})

# Rules
%.o:		%.c
	${CC} ${CFLAGS} -c ${INCLUDES} $< -o $@
	@echo "${PREFIX}Compilation of $<..."

all:	$(CLIENT) $(SERVER)

bonus:	all

$(CLIENT):	${OBJS_CLIENT} ${OBJS}
	${MAKE_LIBFT}
	${CC} ${CFLAGS} ${INCLUDES} $^ ${LIBFT_FOLDER}/${LIBFT_NAME} -o $@

$(SERVER):	${OBJS_SERVER} ${OBJS}
	${MAKE_LIBFT}
	${CC} ${CFLAGS} ${INCLUDES} $^ ${LIBFT_FOLDER}/${LIBFT_NAME} -o $@


clean:
	${MAKE_LIBFT} clean
	@rm -f ${OBJS} ${OBJS_CLIENT} ${OBJS_SERVER}

fclean:
	${MAKE_LIBFT} fclean
	@rm -f ${CLIENT} ${SERVER} ${OBJS} ${OBJS_CLIENT} ${OBJS_SERVER}

re:		fclean all

.PHONY:	all clean fclean re
