/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:23:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/02 15:11:05 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_garbage	g_gbg;

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

static int	getfd_infile(t_cmd *cmd, char *file_name, \
		char **error_msg, t_token *token)
{
	struct stat	buffer;

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
		if (!stat(file_name, &buffer))
			*error_msg = error_buffer(*error_msg, file_name, 3, token);
		else
			*error_msg = error_buffer(*error_msg, file_name, 1, token);
		if (!*error_msg)
			return (1);
	}
	return (0);
}

static int	getfd_heredoc(t_cmd *cmd, t_token *token, \
		t_data *data, char **error_msg)
{
	pid_t	pid;
	int		res;

	cmd->is_heredoc = 2;
	pid = fork();
	if (!pid)
		heredoc_child(data, cmd, token);
	signal(SIGINT, SIG_IGN);
	wait(&res);
	if (res == 256)
		return (unlink(cmd->heredoc), 2);
	return (getfd_infile(cmd, cmd->heredoc, error_msg, token), 0);
}

static int	getfd_outfile(t_cmd *cmd, t_token *token, char **error_msg)
{
	int	open_option;

	if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
		return (0);
	if (cmd->fd_outfile > 2)
		close(cmd->fd_outfile);
	if (token->type == GREAT)
		open_option = O_TRUNC;
	else
		open_option = O_APPEND;
	cmd->fd_outfile = open(token->token, \
			O_WRONLY | open_option | O_CREAT, 0644);
	if (cmd->fd_outfile == -1)
	{
		*error_msg = error_buffer(*error_msg, token->token, 2, token);
		if (!*error_msg)
			return (1);
	}
	return (0);
}

int	token_to_cmd(t_token *token, t_data *data, int i)
{
	int		ret;
	char	*error_msg;

	ret = 0;
	g_gbg.new_cmd = lstnew_cmd(i);
	if (!g_gbg.new_cmd)
		return (1);
	error_msg = NULL;
	while (token)
	{
		if (token->type == WORD && (token->token[0] || \
			(!token->token[0] && !token->expanded)))
			ret = add_optioncmd(g_gbg.new_cmd, token);
		else if (token->type == LESS)
			ret = getfd_infile(g_gbg.new_cmd, token->token, &error_msg, token);
		else if (token->type == HEREDOC)
			ret = getfd_heredoc(g_gbg.new_cmd, token, data, &error_msg);
		else if (token->type == GREAT || token->type == GREATGREAT)
			ret = getfd_outfile(g_gbg.new_cmd, token, &error_msg);
		if (ret)
			return (lstdelone_cmd(g_gbg.new_cmd), ret);
		token = token->next;
	}
	return (ft_putstr_fd(error_msg, 2), free(error_msg), \
			lstadd_back_cmd(&(data->cmd), g_gbg.new_cmd), 0);
}
