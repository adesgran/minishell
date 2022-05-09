/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/09 15:08:44 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int run_again = 1;
void	get_sig(int sig)
{
	if (sig == SIGINT)
	{
		run_again = 0;
		printf("\nLeave with Ctrl-C\n");
	}
	else if (sig == SIGQUIT)
	{
		run_again = 0;
		printf("\nLeave with Ctrl-\\\n");
	}
}

int	loop_read(void)
{
	char	*line;

	signal(SIGINT, get_sig);
	signal(SIGQUIT, get_sig);
	while (run_again)
	{
		line = readline("\x1B[34m\033[1mminishell$> \x1B[0m");
		add_history(line);
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
