NAME = minishell

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

C_FILES = $(wildcard *.c)
C_FILES += $(wildcard lst_token/*.c)
C_FILES += $(wildcard lst_cmd/*.c)
O_FILES = $(C_FILES:.c=.o)

LIBFT = libft/libft.a
LIBFT_INC = -L libft -lft
LIBFT_DIR = libft
LIBFT_H = libft/libft.h
LIBFT_REPO = https://github.com/adesgran/libft_extended.git

LIBS_FLAGS = -lreadline

INCLUDES = -I ${LIBFT_DIR} -I . -I lst_token -I lst_cmd

.c.o:
		${CC} ${C_FLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

all: ${LIBFT} ${NAME}

${LIBFT}:
		if [ ! -d "./libft" ]; then git clone ${LIBFT_REPO} libft; fi
		make -C libft

${NAME}: ${O_FILES}
		${CC} ${O_FILES} ${LIBFT_INC} ${LIBS_FLAGS} -o ${NAME}

clean:
		rm -r ${O_FILES}
		make clean -C ${LIBFT_DIR}

fclean: clean
		rm -r ${NAME}
		make fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re ${NAME}
