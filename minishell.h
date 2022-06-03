/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:53:59 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:54 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COL_DEFAULT "\x1B[0m"
# define COL_RED "\x1B[31m"
# define COL_GRN "\x1B[32m"
# define COL_YEL "\x1B[33m"
# define COL_BLU "\x1B[34m"
# define COL_MAG "\x1B[35m"
# define COL_CYN "\x1B[36m"
# define COL_WHT "\x1B[37m"
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
# include <errno.h>

typedef struct s_token
{
	char			*token;
	int				expanded;
	int				type;
	char			*unexpanded;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			*bin_path;
	int				fd_infile;
	int				fd_outfile;
	int				is_heredoc;
	char			*heredoc;
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
	char	*last_cmd_status;
	t_token	*token;

}	t_data;

typedef struct s_garbage
{
	t_data	*data;
	char	**line_tab;
	t_cmd	*new_cmd;
	int		fd_heredoc;
}	t_garbage;

// main.c
void	free_data(t_data *data);
void	free_garbage(int is_unlink);

// get_line.c
char	*get_line(t_data *data);

//debugage.c
void	print_token(t_token *token);
void	print_cmd(t_cmd *cmd);

// pipex.c
int		add_outfile(t_cmd *cmd, int new_fd);
int		pipex(t_data *data, t_cmd *cmd);

// data_functions.c
void	free_data(t_data *data);
t_data	*init_data(char **env);
void	increment_shlvl(t_data *data);

// env_built_in.c
int		is_env_built_in(t_cmd *cmd);
int		env_built_in(t_data *data, t_cmd *cmd);
void	call_built_in_fork(t_data *data, t_cmd *cmd);

// get_bin_path.c
char	**get_path(t_data *data);
int		get_bin_path(t_cmd *cmd, char **paths);
int		is_relative_path(t_cmd *cmd);
char	*get_relative_path(t_cmd *cmd);

// built_in
int		mini_echo(char **av);
int		mini_env(t_data *data);
int		mini_pwd(t_data *data);
int		mini_unset(t_data *data, char **strs);
int		mini_cd(t_data *data, char **cmd);
int		mini_export(t_data *data, char **cmd);
int		mini_exit(t_data *data, char **cmd, int infork);
void	export_empty(t_data *data);

// env_struct_ft.c
void	free_env(t_env *env);
t_env	*get_var_env(t_env *env, char *var);
t_env	*remove_var_env(t_env *env, char *var);
void	push_back_env(t_env *env, char *var, char *value);
t_env	*init_env(char **env);
char	**env_to_tab(t_env *env);
t_env	*init_empty_env(void);

// lst_cmd.c
t_cmd	*lstnew_cmd(int i);
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
int		token_to_cmd(t_token *token, t_data *data, int i);

// minisplit.c
char	**split_pipes(char *str, int *ret);

// ft_remove_quotes.c
int		ft_remove_quotes(t_token *token);

// ft_expander.c
int		lf_var(char **token, t_env *env, char *last_cmd_status, int is_heredoc);
int		expander(t_token *token, t_env *env, char *last_cmd_value);

//sig_handler.c
void	get_sig_heredoc(int sig);
void	get_sig_child(int sig);

//heredoc_child.c
void	heredoc_child(t_data *data, t_cmd *cmd, t_token *token);

//error_buffer.c
char	*error_buffer(char *old_msg, char *file_name, int type, t_token *token);

char	*ft_tabjoin(char **strs, char *sep);

#endif
