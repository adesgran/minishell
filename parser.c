/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:23:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/16 12:47:29 by mchassig         ###   ########.fr       */
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

static void	getfd_infile(t_cmd *cmd, char *file_name)
{
	if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
		return ;
	if (cmd->is_heredoc)
		unlink("heredoc");
	else if (cmd->fd_infile > 2)
		close(cmd->fd_infile);
	cmd->fd_infile = open(file_name, O_RDONLY);
	if (cmd->fd_infile == -1)
		perror(file_name);
}

static int	getfd_heredoc(t_cmd *cmd, char *limiter)
{
	int		fd;
	char	*line;
	char	*new_limiter;

	fd = open("heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (perror("heredoc"), 1);
	cmd->is_heredoc = 1;
	new_limiter = ft_strjoinx(2, limiter, "\n");
	if (!new_limiter)
		return (close(fd), 1);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			return (close(fd), free(new_limiter), 1);
		if (ft_strncmp(line, new_limiter, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = NULL;
	}
	close(fd);
	return (free(line), free(new_limiter), getfd_infile(cmd, "heredoc"), 0);
}

static void	getfd_outfile(t_cmd *cmd, char *file_name, int type)
{
	int	open_option;

	if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
		return ;
	if (cmd->fd_outfile > 2)
		close(cmd->fd_outfile);
	if (type == GREAT)
		open_option = O_TRUNC;
	else
		open_option = O_APPEND;
	cmd->fd_outfile = open(file_name, O_WRONLY | open_option | O_CREAT, 0644);
	if (cmd->fd_outfile == -1)
		perror(file_name);
}

int	token_to_cmd(t_token *token, t_cmd **cmd)
{
	t_cmd	*new;
	int		ret;

	ret = 0;
	new = lstnew_cmd();
	if (!new)
		return (lstclear_token(&token), lstclear_cmd(cmd), 1);
	while (token)
	{
		if (token->type == WORD)
			new->cmd = add_optioncmd(new->cmd, token);
		else if (token->type == LESS)
			getfd_infile(new, token->token);
		else if (token->type == HEREDOC)
			ret = getfd_heredoc(new, token->token);
		else if (token->type == GREAT || token->type == GREATGREAT)
			getfd_outfile(new, token->token, token->type);
		if ((!new->cmd && token->token == WORD) || ret)
			return (lstclear_token(&token), lstclear_cmd(cmd),
				lstdelone_cmd(new), 1);
		token = token->next;
	}
	return (lstclear_token(&token), lstadd_back_cmd(cmd, new), 0);
}
