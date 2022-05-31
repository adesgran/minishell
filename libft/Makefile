NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

GNL = $(wildcard gnl/*.c)
FT_PRINTF = $(wildcard ft_printf/*.c)
MEM = $(wildcard mem/*.c)
LST = $(wildcard lst/*.c)
STR = $(wildcard str/*.c)
TAB = $(wildcard tab/*.c)

C_FILES = ${GNL} ${FT_PRINTF} ${MEM} ${LST} ${STR} ${TAB}

O_FILES = ${C_FILES:c=o}
H_FILES = -I .

%.o: %.c
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} ${H_FILES} -c $< -o $@

all: ${NAME}

${NAME}: ${O_FILES}
	@echo "\n"
	@echo "\033[0;32mCompiling Libft.."
	@ar rc ${NAME} ${O_FILES}
	@ranlib $(NAME) 
	@echo "\n\033[0mDone !"

clean:
	@echo "\033[0;31mCleaning libft binaries..."
	@rm -f ${O_FILES}
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mCleaning libft..."
	@rm -f ${NAME}
	@echo "\033[0m"

re: fclean all
