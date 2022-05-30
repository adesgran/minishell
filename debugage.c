/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:58:46 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/27 17:51:31 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token(t_token *token)
{
	printf("*token***************\n");
	while (token)
	{
		printf("	token = %s // type %d\n", token->token, token->type);
		token = token->next;
	}
	printf("*token***************\n");
}

void	print_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("*cmd***************\n");
		printf("	cmd : %s\n", cmd->cmd[0]);
		printf("	bin : %s\n", cmd->bin_path);
		printf("	fd_infile : %d\n", cmd->fd_infile);
		printf("	fd_outfile : %d\n", cmd->fd_outfile);
		printf("	heredoc : %s\n", cmd->heredoc);
		printf("	next : %p\n", cmd->next);
		printf("*cmd***************\n");
		cmd = cmd->next;
	}
}
