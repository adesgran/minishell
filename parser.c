/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:23:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/14 18:19:47 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**add_optioncmd(char **cmd, t_token *token)
{
	char	**new_cmd;
	int		size;
	int		i;

	size = 0;
	while (cmd && cmd[size])
		size++;
	new_cmd = malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (NULL);
	new_cmd[size + 1] = NULL;
	i = 0;
	while (cmd && cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	free(cmd);
	new_cmd[i] = token->token;
	token->token = NULL;
	return (new_cmd);
}

static int	getfd_infile(int prev_fd, char *file_name, t_cmd *cmd)
{
	int	new_fd;

	if (cmd->fd_infile == -1 || (cmd->fd_outfile
		&& cmd->fd_outfile[cmd->nb_outfile - 1] == -1))
		return (-1);
	if (prev_fd > 2)
		close(prev_fd);
	new_fd = open(file_name, O_RDONLY);
	if (new_fd == -1)
		return (perror(file_name), -1);
	return (new_fd);
}

static int	getfd_heredoc(int prev_fd, char *limiter, t_cmd *cmd)
{
	int		new_fd;
	char	*line;
	char	*new_limiter;

	new_fd = open("here_doc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (new_fd == -1)
		return (-1);
	new_limiter = ft_strjoinx(2, limiter, "\n");
	if (!new_limiter)
		return (close(new_fd), -1);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			return (close(new_fd), free(new_limiter), -1);
		if (ft_strncmp(line, new_limiter, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, new_fd);
		free(line);
		line = NULL;
	}
	close(new_fd);
	return (free(line), free(new_limiter), getfd_infile(prev_fd, "here_doc", cmd));
}

static int	getfd_outfile(t_cmd *cmd, char *file_name, int type/*int open_option*/)
{
	int	new_fd;
	int	open_option;
	
	if (cmd->fd_infile == -1 || (cmd->fd_outfile
		&& cmd->fd_outfile[cmd->nb_outfile - 1] == -1))
		return (0);
	if (type == GREAT)
		open_option = O_TRUNC;
	else
		open_option = O_APPEND;
	new_fd = open(file_name, O_WRONLY | open_option | O_CREAT, 0644);
	if (new_fd == -1)
		perror(file_name);
	if (add_outfile(cmd, new_fd))
		return (close(new_fd), 1);
	return (0);
}

int	token_to_cmd(t_token *token, t_cmd **cmd)
{
	t_cmd	*new;
	int		ret;
	
	new = lstnew_cmd();
	if (!new)
		return (lstclear_token(&token), lstclear_cmd(cmd), 1);
	while (token)
	{
		if (token->type == WORD)
			new->cmd = add_optioncmd(new->cmd, token);
		else if (token->type == LESS)
			new->fd_infile = getfd_infile(new->fd_infile, token->token, new);
		else if (token->type == HEREDOC)
			new->fd_infile = getfd_heredoc(new->fd_infile, token->token, new);
		else if (token->type == GREAT || token->type == GREATGREAT)
			ret = getfd_outfile(new, token->token, token->type/*O_TRUNC*/);
		// else if (token->type == GREATGREAT)
		// 	getfd_outfile(new, token->token, O_APPEND);
		if ((token->type == WORD && !new->cmd) || ret == 1)
			return (lstclear_token(&token), lstclear_cmd(cmd),
				lstdelone_cmd(new), 1);
		token = token->next;
	}
	// if (new->fd_infile != 1 && !new->fd_outfile)
	// {
	// 	new->fd_outfile = malloc(sizeof(int) * ++new->nb_outfile);
	// 	if (!new->fd_outfile)
	// 		return (lstclear_token(&token), lstclear_cmd(cmd),
	// 			lstdelone_cmd(new), 1);
	// 	new->fd_outfile[0] = 1;
	// }
	return (lstclear_token(&token), lstadd_back_cmd(cmd, new), 0);
}
