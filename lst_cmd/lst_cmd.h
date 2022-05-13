#ifndef LST_CMD_H
# define LST_CMD_H

typedef struct s_cmd
{
	char			**cmd;
	char			*bin_path;
	int				fd_infile;
	int				fd_outfile;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*lstnew_cmd(void);
void	lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void	lstclear_cmd(t_cmd **lst);
void	lstdelone_cmd(t_cmd *lst);
t_cmd	*lstlast_cmd(t_cmd *lst);

#endif