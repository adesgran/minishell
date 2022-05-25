valgrind --suppressions=cmd_valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
vim valgrind-out.txt
