#ifndef LST_TOKEN_H
# define LST_TOKEN_H

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

t_token	*lstnew_token(char *token, int type);
void	lstadd_back_token(t_token **alst, t_token *new);
t_token	*lstlast_token(t_token *lst);
void	lstclear_token(t_token **lst);
void	lstdelone_token(t_token *lst);

#endif