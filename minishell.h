/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:53:59 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/25 13:12:51 by adesgran         ###   ########.fr       */
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
# include <dirent.h>

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			*bin_path;
	int				fd_infile;
	int				fd_outfile;
	int				is_heredoc;
	struct s_cmd	*next;
}	t_cmd;

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

// ************* TO ADD TO LIBFT *****************
int		ft_ischarset(char c, char *charset);

// main.c
void	free_data(t_data *data);

//debugage.c
void	print_token(t_token *token);
void	print_cmd(t_cmd *cmd);

// pipex.c
int		add_outfile(t_cmd *cmd, int new_fd);
int		pipex(t_data *data, t_cmd *cmd);
int		is_env_built_in(t_cmd *cmd);
int		env_built_in(t_data *data, t_cmd *cmd);

// get_bin_path.c
char	**get_path(t_data *data);
int		get_bin_path(t_cmd *cmd, char **paths);

// built_in
int		mini_echo(char **av);
int		mini_env(t_data *data);
int		mini_pwd(t_data *data);
int		mini_unset(t_data *data, char **strs);
int		mini_cd(t_data *data, char **cmd);
int		mini_export(t_data *data, char **cmd);

// utils
char	*ft_remove_quotes(char *str);

// env_struct_ft.c
void	free_env(t_env *env);
t_env	*get_var_env(t_env *env, char *var);
t_env	*remove_var_env(t_env *env, char *var);
void	push_back_env(t_env *env, char *var, char *value);
t_env	*init_env(char **env);

// lst_cmd.c
t_cmd	*lstnew_cmd(void);
void	lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void	lstclear_cmd(t_cmd **lst);
void	lstdelone_cmd(t_cmd *lst);
t_cmd	*lstlast_cmd(t_cmd *lst);

//lst_token.c
t_token	*lstnew_token(char *token, int type);
void	lstadd_back_token(t_token **alst, t_token *new);
t_token	*lstlast_token(t_token *lst);
void	lstclear_token(t_token **lst);
void	lstdelone_token(t_token *lst);

// lexer.c
int		lexer(char *str, t_token **token);

//parsing.c
int		token_to_cmd(t_token *token, t_cmd **cmd);

// minisplit.c
char	**split_pipes(char *str, int *ret);

// ft_remove_quotes.c
char	*ft_remove_quotes(char *str);

// ft_expander.c
int		expander(t_token *token, t_env *env);

#endif
