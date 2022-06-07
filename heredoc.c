/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:30:02 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/07 18:29:32 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	g_gbg;

void	heredoc_child(t_data *data, t_token *token, char *heredoc_name)
{	
	char	*line;

	g_gbg.fd_heredoc = open(heredoc_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	g_gbg.data = data;
	if (g_gbg.fd_heredoc == -1)
		return (free_garbage(), exit(1));
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
		if (!token->expanded
			&& lf_var(&line, data->env, data->last_cmd_status, 1) == -1)
			exit(EXIT_FAILURE);
		ft_putendl_fd(line, g_gbg.fd_heredoc);
		line = (free(line), NULL);
	}
	return (free(line), free_garbage(), exit(0));
}

static char	*gen_heredoc_name(t_token *token, int num)
{
	char	*heredoc_num;
	char	*heredoc_name;

	token->expanded = ft_remove_quotes(token);
	if (token->expanded == -1)
		return (NULL);
	heredoc_num = ft_itoa(num);
	if (!heredoc_num)
		return (NULL);
	heredoc_name = ft_strjoin("heredoc", heredoc_num);
	free(heredoc_num);
	return (heredoc_name);
}

int	create_heredoc(t_data *data, t_token *token, int num)
{
	pid_t	pid;
	int		res;

	g_gbg.heredoc_name = gen_heredoc_name(token, num);
	if (!g_gbg.heredoc_name)
		return (1);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
		heredoc_child(data, token, g_gbg.heredoc_name);
	signal(SIGINT, SIG_IGN);
	wait(&res);
	res = res / 256;
	if (res == 1)
		return (unlink(g_gbg.heredoc_name), free(g_gbg.heredoc_name), 2);
	if (res == 130)
	{
		free(data->last_cmd_status);
		data->last_cmd_status = ft_strdup("130");
		return (unlink(g_gbg.heredoc_name), free(g_gbg.heredoc_name), 2);
	}
	free(token->token);
	token->token = g_gbg.heredoc_name;
	return (0);
}
