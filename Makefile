NAME = minishell

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

C_FILES = data_functions.c debugage.c env_built_in.c env_struct_ft.c env_to_tab.c \
		 expander.c ft_remove_quotes.c get_bin_path.c lexer.c lst_cmd.c lst_token.c \
		 main.c minisplit.c parser.c pipex.c \
		 built_in/cd.c built_in/echo.c built_in/env.c built_in/exit.c built_in/export.c \
		 built_in/export_empty.c built_in/pwd.c built_in/unset.c

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

.PHONY: all clean fclean re
