/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:23:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 15:37:52 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**add_optioncmd(char **cmd, t_token *token)
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

int	getfd_infile(int prev_fd, char *file_name)
{
	int	new_fd;

	if (prev_fd != -2)
		close(prev_fd);
	new_fd = open(file_name, O_RDONLY);
	if (new_fd == -1)
		return (perror(file_name), -1);
	return (new_fd);
}

int	getfd_heredoc(int prev_fd, char *limiter)
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
		ft_putstr_fd("pipe heredoc> ", 1);
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
	return (free(line), free(new_limiter), getfd_infile(prev_fd, "here_doc"));
}

int	getfd_outfile(int prev_fd, char *file_name, int open_option)
{
	int	new_fd;

	if (prev_fd != -2)
		close(prev_fd);
	new_fd = open(file_name, O_WRONLY | open_option | O_CREAT, 0644);
	if (new_fd == -1)
		return (perror(file_name), -1);
	return (new_fd);
}

void	token_to_cmd(t_token *token, t_cmd **cmd)
{
	t_cmd	*new;

	new = lstnew_cmd();
	if (!new)
		return (lstclear_cmd(cmd));
	while (token)
	{
		if (token->type == WORD)
			new->cmd = add_optioncmd(new->cmd, token);
		else if (token->type == LESS)
			new->fd_infile = getfd_infile(new->fd_infile, token->token);
		else if (token->type == HEREDOC)
			new->fd_infile = getfd_heredoc(new->fd_infile, token->token);
		else if (token->type == GREAT)
			new->fd_outfile = getfd_outfile(new->fd_infile,
					token->token, O_TRUNC);
		else if (token->type == GREATGREAT)
			new->fd_outfile = getfd_outfile(new->fd_infile,
					token->token, O_APPEND);
		if ((token->type == WORD && !new->cmd))
			return (lstclear_cmd(cmd), lstdelone_cmd(new));
		token = token->next;
	}
	lstadd_back_cmd(cmd, new);
}
