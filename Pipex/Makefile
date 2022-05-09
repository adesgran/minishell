NAME = pipex
CC = gcc
LEAKS = -g -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror ${LEAKS}
SRCS = main.c parsing.c struct.c ft_split.c pipex_utils.c
OBJS = ${SRCS:.c=.o}
SRCS_BONUS = main_bonus.c parsing_bonus.c struct_bonus.c ft_split_bonus.c pipex_utils_bonus.c get_next_line_bonus.c
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $<

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^ -I .

clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -f ${NAME}

bonus: ${OBJS_BONUS}
	${CC} ${CFLAGS} -o ${NAME} $^ -I .

re: fclean all
