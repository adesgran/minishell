/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:53:59 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/19 17:33:50 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define WORD 0
# define LESS 60
# define HEREDOC 61
# define GREAT 62
# define GREATGREAT 63

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
# include <lst_token.h>
# include <lst_cmd.h>
# include <dirent.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;
	char	**envp;
	int		n_cmd;
}	t_data;

// main.c
void	print_cmd(t_cmd *cmd);

// pipex.c
int		add_outfile(t_cmd *cmd, int new_fd);
int		pipex(t_data *data);

// get_bin_path.c
char	**get_path(t_data *data);
int		get_bin_path(t_cmd *cmd, char **paths);

// built_in
int		mini_echo(char **av);
int		mini_env(t_data *data);
int		mini_pwd(t_data *data);
int		mini_unset(t_data *data, char **strs);
int		mini_cd(t_data *data, char *str);
int		mini_export(t_data *data, char *str);

// utils
char	*ft_remove_quotes(char *str);

// env_struct_ft.c
void	free_env(t_env *env);
t_env	*get_var_env(t_env *env, char *var);
t_env	*remove_var_env(t_env *env, char *var);
void	push_back_env(t_env *env, char *var, char *value);
t_env	*init_env(char **env);

// lexer.c
int		lexer(char *str, t_token **token);

//parsing.c
int		token_to_cmd(t_token *token, t_cmd **cmd);

// minisplit.c
char	**split_pipes(char *str);

// ft_remove_quotes.c
char	*ft_remove_quotes(char *str);

// ft_expender.c
int	expender(t_token *token, t_env *env);

int	ft_ischarset(char c, char *charset);


#endif
