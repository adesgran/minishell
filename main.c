/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/16 12:46:34 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_sig(int sig)
{
	(void)sig;
}

void	free_data(t_data *data)
{
	free_env(data->env);
	lstclear_cmd(&(data->cmd));
	free(data);
}

static t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->cmd = NULL;
	data->env = init_env(env);
	if (!data->env)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	data->envp = env;
	return (data);
}

static int	analyse_line(char **line_tab, t_data *data)
{
	t_token	*token;
	int		i;

	if (!line_tab)
		return (1);
	i = 0;
	while (line_tab[i])
	{
		token = NULL;
		if (lexer(line_tab[i], &token) == 1)
			return (ft_free_tabstr(line_tab), 1);
		if (token_to_cmd(token, &(data->cmd)) == 1)
			return (ft_free_tabstr(line_tab), 1);
		i++;
	}
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		ft_printf("***************\n");
		ft_printf("	cmd : %s\n", cmd->cmd[0]);
		ft_printf("	bin : %s\n", cmd->bin_path);
		ft_printf("	fd_infile : %d\n", cmd->fd_infile);
		ft_printf("	fd_outfile : %d\n", cmd->fd_outfile);
		printf("	next : %p\n", cmd->next);
		printf("***************\n");
		cmd = cmd->next;
	}
}

static int	loop_read(t_data *data)
{
	char	*line;

	// signal(SIGINT, get_sig);
	// signal(SIGQUIT, get_sig);
	printf("\x1B[32mWelcome to Minishell !\x1B[0m\n");
	while (1)
	{
		line = readline("\x1B[34m\033[1mminishell$> \x1B[0m");
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			printf("\x1B[31mGood Bye !\x1B[0m\n");
			return (rl_clear_history(), free(line), free_data(data), 0);
		}
		add_history(line);
		if (line[0])
		{
			if (analyse_line(split_pipes(line), data) == 1)
				return (free_data(data), free(line), 1);
			if (get_bin_path(data->cmd, get_path(data)) == 1)
				return (free_data(data), free(line), 1);
			pipex(data);
			lstclear_cmd(&(data->cmd));
		}
		free(line);
	}
	return (rl_clear_history(), 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = init_data(env);
	loop_read(data);
	(void)ac;
	(void)av;
	return (0);
}
