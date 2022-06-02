/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:30:02 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 18:16:17 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	g_gbg;

void	heredoc_child(t_data *data, t_cmd *cmd, t_token *token)
{	
	char	*line;

	g_gbg.fd_heredoc = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	g_gbg.data = data;
	if (g_gbg.fd_heredoc == -1)
		exit(1);
	while (1)
	{
		signal(SIGINT, get_sig_heredoc);
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document at line %d", data->n_cmd);
			printf(" delimited by end-of-file (wanted `%s')\n", token->token);
			break ;
		}
		if (ft_strcmp(line, token->token) == 0)
			break ;
		if (!token->expanded && lf_var(&line, data->env, data->last_cmd_status, 1) == -1)
			exit(EXIT_FAILURE);
		ft_putendl_fd(line, g_gbg.fd_heredoc);
		line = (free(line), NULL);
	}
	return (free(line), free_garbage(0), exit(0));
}
