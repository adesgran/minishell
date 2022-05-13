/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 15:58:12 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_sig(int sig)
{
	(void)sig;
}

int	loop_read(char **env)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;
	
	// signal(SIGINT, get_sig);
	// signal(SIGQUIT, get_sig);
	(void)env;
	printf("\x1B[32mWelcome to Minishell !\x1B[0m\n");
	while (1)
	{
		token = NULL;
		cmd = NULL;
		line = readline("\x1B[34m\033[1mminishell$> \x1B[0m");
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			printf("\x1B[31mGood Bye !\x1B[0m\n");
			free(line);
			break ;
		}
		add_history(line);
		lexer(line, &token);
		if (!token && line[0])
			return (free(line), lstclear_token(&token), 1); // + free des trucs
		token_to_cmd(token, &cmd);
		if (!cmd)
			return (free(line), lstclear_token(&token), 1); // + free des trucs
		// get_bin_path(cmd);
		lstclear_token(&token);
		lstclear_cmd(&cmd);
		free(line);
	}
	rl_clear_history();
	return (0);
}

int	main(int ac, char **av, char **env)
{
	loop_read(env);	
	(void)ac;
	(void)av;
	return (0);
}
