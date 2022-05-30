NAME = minishell

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

C_ROOT = data_functions debugage env_built_in env_struct_ft env_to_tab expander \
		 ft_remove_quotes get_bin_path lexer lst_cmd lst_token main minisplit parser pipex
C_BUILTIN = cd echo env exit export export_empty pwd unset

C_FILES = $(addsuffix .c, $(C_ROOT)) $(addsuffix .c, $(addprefix built_in/, $(C_BUILTIN)))

O_FILES = $(C_FILES:c=o)

LIBFT = libft/libft.a
LIBFT_INC = -L libft -lft
LIBFT_DIR = libft
LIBFT_H = libft/libft.h
LIBFT_REPO = https://github.com/adesgran/libft_extended.git

LIBS_FLAGS = -lreadline

INCLUDES = -I ${LIBFT_DIR} -I . -I lst_token -I lst_cmd

all: ${NAME}

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${C_FLAGS} ${INCLUDES} -c $< -o $@

${NAME}: $(O_FILES)
	@echo "\n"
	@if [ ! -d "./libft" ]; then git clone ${LIBFT_REPO} libft; fi
	@make -C libft
	@echo "\n\033[0;34mCompiling minshell..."
	@${CC} ${O_FILES} ${LIBFT_INC} ${LIBS_FLAGS} -o ${NAME}

clean:
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(O_FILES)
	@echo "\033[0m"

fclean: clean
	@make fclean -C libft/
	@echo "\n\033[0;31mDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
