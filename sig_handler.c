/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:55:00 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/03 21:10:24 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	g_gbg;

void	get_sig_child(int sig)
{
	char	*prompt;

	if (sig == SIGINT)
	{
		free(g_gbg.data->last_cmd_status);
		g_gbg.data->last_cmd_status = ft_strdup("130");
		prompt = get_prompt(g_gbg.data);
		printf("\n%s", prompt);
		free(prompt);
		rl_replace_line("", 0);
		//rl_on_new_line();
		//rl_redisplay();
	}
}

void	get_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		close(g_gbg.fd_heredoc);
		free_garbage(1);
		exit(130);
	}
}
