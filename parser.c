/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:23:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/31 15:50:27 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_error(char *old_msg, char *file_name, int type)
{
	char	*new_msg;
	char	*type_msg;
	
	if (type == 1 || (type == 2 && !ft_strlen(file_name)))
		type_msg = ": No such file or directory\n";
	else
		type_msg = ": Persmission denied\n";
	if (!old_msg)
		new_msg = ft_strjoin(file_name, type_msg);
	else
		new_msg = ft_strjoinx(3, old_msg, file_name, type_msg);
	return (free(old_msg), new_msg);
}

static int	add_optioncmd(t_cmd *cmd, t_token *token)
{
	char	**new_cmd;
	int		size;
	int		i;

	size = 0;
	while (cmd->cmd && cmd->cmd[size])
		size++;
	new_cmd = malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (1);
	new_cmd[size + 1] = NULL;
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		new_cmd[i] = cmd->cmd[i];
		i++;
	}
	free(cmd->cmd);
	new_cmd[i] = token->token;
	token->token = NULL;
	cmd->cmd = new_cmd;
	return (0);
}

static int	getfd_infile(t_cmd *cmd, char *file_name, char **error_msg)
{
	if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
		return (0);
	if (cmd->is_heredoc == 1)
	{
		unlink(cmd->heredoc);
		cmd->is_heredoc = 0;
	}
	else if (cmd->is_heredoc == 2)
		cmd->is_heredoc = 1;
	if (cmd->fd_infile > 2)
		close(cmd->fd_infile);
	cmd->fd_infile = open(file_name, O_RDONLY);
	if (cmd->fd_infile == -1)
	{
		*error_msg = add_error(*error_msg, file_name, 1);
		if (!*error_msg)
			return (1);
	}
	return (0);
}

static int	getfd_heredoc(t_cmd *cmd, char *limiter, t_data *data, char **error_msg)
{
	int		fd;
	char	*line;

	fd = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (1);
	cmd->is_heredoc = 2;
	while (1)
	{

		line = readline("> ");
		if (!line)
			return (close(fd), 1);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		line = lf_var(line, data->env, data->last_cmd_status, 1);
		ft_putendl_fd(line, fd);
		free(line);
		line = NULL;
	}
	return (free(line), getfd_infile(cmd, cmd->heredoc, error_msg), 0);
}

static int	getfd_outfile(t_cmd *cmd, char *file_name, int type, char **error_msg)
{
	int	open_option;

	if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
		return (0);
	if (cmd->fd_outfile > 2)
		close(cmd->fd_outfile);
	if (type == GREAT)
		open_option = O_TRUNC;
	else
		open_option = O_APPEND;
	cmd->fd_outfile = open(file_name, O_WRONLY | open_option | O_CREAT, 0644);
	if (cmd->fd_outfile == -1)
	{
		*error_msg = add_error(*error_msg, file_name, 2);
		if (!*error_msg)
			return (1);
	}
	return (0);
}

int	token_to_cmd(t_token *token, t_cmd **cmd, t_data *data, int i)
{
	t_cmd	*new;
	int		ret;
	char	*error_msg;
	
	ret = 0;
	new = lstnew_cmd(i);
	if (!new)
		return (lstclear_cmd(cmd), 1);
	error_msg = NULL;
	while (token)
	{
		if (token->type == WORD)
			ret = add_optioncmd(new, token);
		else if (token->type == LESS)
			ret = getfd_infile(new, token->token, &error_msg);
		else if (token->type == HEREDOC)
			ret = getfd_heredoc(new, token->token, data, &error_msg);
		else if (token->type == GREAT || token->type == GREATGREAT)
			ret = getfd_outfile(new, token->token, token->type, &error_msg);
		if (ret)
			return (lstclear_cmd(cmd), lstdelone_cmd(new), 1);
		token = token->next;
	}
	ft_putstr_fd(error_msg, 2);
	return (lstadd_back_cmd(cmd, new), 0);
}
