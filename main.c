/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/12 10:56:48 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_sig(int sig)
{
	(void)sig;
}

int	loop_read(void)
{
	char	*line;
	t_token	*token;

	// signal(SIGINT, get_sig);
	// signal(SIGQUIT, get_sig);
	token = NULL;
	printf("\x1B[32mWelcome to Minishell !\x1B[0m\n");
	while (1)
	{
		line = readline("\x1B[34m\033[1mminishell$> \x1B[0m");
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			printf("\x1B[31mGood Bye !\x1B[0m\n");
			free(line);
			break ;
		}
		add_history(line);
		lexer(line, &token);
		free(line);
	}
	rl_clear_history();
	return (0);
}

int	main(int ac, char **av)
{
	loop_read();	
	(void)ac;
	(void)av;
	return (0);
}
