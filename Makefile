# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marykman <marykman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/08 00:02:10 by mykman            #+#    #+#              #
#    Updated: 2023/11/15 19:10:12 by marykman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC				=	@gcc
CFLAGS			=	-Wall -Wextra -Werror

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
LIBFT_FOLDER	=	libft/
LIBFT_NAME		=	libft.a
MAKE_LIBFT		=	@make -s -C ${LIBFT_FOLDER}
LIBFT			=	${LIBFT_FOLDER}/${LIBFT_NAME}

# Files
INCLUDES		=	-I./includes \
					-I./${LIBFT_FOLDER}/includes
SRCS			=	minitalk.c
SRCS_CLIENT		=	client.c
SRCS_SERVER		=	server.c

OBJS			=	$(addprefix srcs/, ${SRCS:.c=.o})
OBJS_CLIENT		=	$(addprefix srcs/, ${SRCS_CLIENT:.c=.o})
OBJS_SERVER		=	$(addprefix srcs/, ${SRCS_SERVER:.c=.o})

HEADERS			=	includes/minitalk.h

# Rules
%.o:		%.c ${HEADERS}
	${CC} ${CFLAGS} -c ${INCLUDES} $< -o $@
	@echo "${PREFIX}Compilation of $<..."

all:	$(CLIENT) $(SERVER)

bonus:	all

$(CLIENT):	${OBJS_CLIENT} ${OBJS} ${LIBFT} ${HEADERS}
	${CC} ${CFLAGS} ${INCLUDES} ${OBJS_CLIENT} ${OBJS} ${LIBFT} -o $@
	@echo "${PREFIX}${GREEN}Client compiled !${RESET}"

$(SERVER): ${OBJS_SERVER} ${OBJS} ${LIBFT} ${HEADERS}
	${CC} ${CFLAGS} ${INCLUDES} ${OBJS_SERVER} ${OBJS} ${LIBFT} -o $@
	@echo "${PREFIX}${GREEN}Server compiled !${RED}"

$(LIBFT):
	${MAKE_LIBFT}

clean:
	${MAKE_LIBFT} clean
	@rm -f ${OBJS} ${OBJS_CLIENT} ${OBJS_SERVER}
	@echo "${PREFIX}${BLUE}Cleaning object files...${RED}"

fclean:
	${MAKE_LIBFT} fclean
	@rm -f ${CLIENT} ${SERVER} ${OBJS} ${OBJS_CLIENT} ${OBJS_SERVER}
	@echo "${PREFIX}${RED}Full clean.${RED}"

re:		fclean all

.PHONY:	all clean fclean re
