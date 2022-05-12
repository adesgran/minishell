#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_DEFAULT "\x1B[0m"
# define COLOR_RED "\x1B[31m"
# define COLOR_GRN "\x1B[32m"
# define COLOR_YEL "\x1B[33m"
# define COLOR_BLU "\x1B[34m"
# define COLOR_MAG "\x1B[35m"
# define COLOR_CYN "\x1B[36m"
# define COLOR_WHT "\x1B[37m"
# define BOLD "\033[1m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
} t_env;

typedef struct s_cmd
{
	char			**cmd;
	char			*bin_path;
	int				fd_infile;
	int				fd_outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;
	char	**envp;
}	t_data;

int		pipex(t_data *data);
void	get_bin_path(t_cmd *cmd);
t_env	*get_var_env(t_env *env, char *var);
void	push_back_env(t_env *env, char *str);
t_env	*init_env(char **env);
void	free_env(t_env *env);

#endif
