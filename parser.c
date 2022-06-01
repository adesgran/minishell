/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:23:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/01 11:27:08 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*g_data;

char	*add_error(char *old_msg, char *file_name, int type, t_token *token)
{
	char	*new_msg;
	char	*type_msg;
	
	if (token->expanded && !ft_strlen(file_name))
	{
		file_name = token->unexpanded;
		type_msg = ": ambiguous redirect\n";
	}
	else if (type == 1 || (type == 2 && !ft_strlen(file_name)))
		type_msg = ": No such file or directory\n";
	else
		type_msg = ": Persmission denied\n";
	if (!old_msg)
		new_msg = ft_strjoinx(3, "minishell: ", file_name, type_msg);
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

static int	getfd_infile(t_cmd *cmd, char *file_name, char **error_msg, t_token *token)
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
		*error_msg = add_error(*error_msg, file_name, 1, token);
		if (!*error_msg)
			return (1);
	}
	return (0);
}

static int	getfd_heredoc(t_cmd *cmd, t_token *token, t_data *data, char **error_msg)
{
	int		fd;
	char	*line;
	pid_t	pid;
	int		res;

	pid = fork();
	if (!pid)
	{
		fd = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		g_data = data;
		if (fd == -1)
			return (1);
		cmd->is_heredoc = 2;
		while (1)
		{
			signal(SIGINT, get_sig_heredoc);
			line = readline("> ");
			if (!line)
			{
				printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", data->n_cmd, token->token);
				break ;
			}
			if (ft_strcmp(line, token->token) == 0)
				break ;
			if (lf_var(&line, data->env, data->last_cmd_status, 1) == -1)
				exit(EXIT_FAILURE);
			ft_putendl_fd(line, fd);
			free(line);
			line = NULL;
		}
		free(line);
		free_data(data);
		exit(0);
	}
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
	cmd->fd_outfile = open(token->token, O_WRONLY | open_option | O_CREAT, 0644);
	if (cmd->fd_outfile == -1)
	{
		*error_msg = add_error(*error_msg, token->token, 2, token);
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
		if (token->type == WORD && (token->token[0] || \
			(!token->token[0] && !token->expanded)))
			ret = add_optioncmd(new, token);
		else if (token->type == LESS)
			ret = getfd_infile(new, token->token, &error_msg, token);
		else if (token->type == HEREDOC)
			ret = getfd_heredoc(new, token, data, &error_msg);
		else if (token->type == GREAT || token->type == GREATGREAT)
			ret = getfd_outfile(new, token, &error_msg);
		if (ret)
			return (lstclear_cmd(cmd), lstdelone_cmd(new), ret);
		token = token->next;
	}
	return (ft_putstr_fd(error_msg, 2), free(error_msg), lstadd_back_cmd(cmd, new), 0);
}
