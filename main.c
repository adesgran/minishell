/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/26 11:02:24 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_sig_parent(int sig)
{
	(void)sig;
}

void	get_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void)sig;
}

void	free_data(t_data *data)
{
	free_env(data->env);
	lstclear_cmd(&(data->cmd));
	free(data->last_cmd_status);
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
	data->n_cmd = 0;
	data->last_cmd_status = ft_itoa(0);
	if (!data->last_cmd_status)
		return (free_env(data->env), free(data), NULL);
	return (data);
}

static int	analyse_line(char *line, t_data *data)
{
	t_token	*token;
	int		i;
	char	**line_tab;
	int		ret;

	ret = 1;
	line_tab = split_pipes(line, &ret);
	free(line);
	if (!line_tab || ret == 2)
		return (ft_free_tabstr(line_tab), ret);
	i = 0;
	while (line_tab[i])
	{
		token = NULL;
		ret = lexer(line_tab[i], &token);
		if (ret)
			return (ft_free_tabstr(line_tab), ret);
		if (expander(token, data->env, data->last_cmd_status))
			return (lstclear_token(&token), ft_free_tabstr(line_tab), 1);
		if (token_to_cmd(token, &(data->cmd), data) == 1)
			return (lstclear_token(&token), ft_free_tabstr(line_tab), 1);
		lstclear_token(&token);
		i++;
	}
	return (ft_free_tabstr(line_tab), 0);
}

static int	loop_read(t_data *data)
{
	char	*line;
	int		ret;

	signal(SIGINT, get_sig_child);
	signal(SIGQUIT, get_sig_child);
	printf("\x1B[32mWelcome to Minishell !\x1B[0m\n");
	while (1)
	{
		line = readline("\x1B[34m\033[1mminishell$> \x1B[0m");
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			if (!line)
				printf("exit\n");
			printf("\x1B[31mGood Bye !\x1B[0m\n");
			return (rl_clear_history(), free(line), 0);
		}
		add_history(line);
		if (line[0])
		{
			ret = analyse_line(line, data);
			if (ret == 1)
				return (1);
			if (ret == 0 && data->cmd->cmd)
			{
				if (get_bin_path(data->cmd, get_path(data)) == 1)
					return (1);
				if (is_env_built_in(data->cmd))
					ret = env_built_in(data, data->cmd);
				else
					ret = pipex(data, data->cmd);
				free(data->last_cmd_status);
				data->last_cmd_status = ft_itoa(ret);
				if (!data->last_cmd_status)
					return (lstclear_cmd(&(data->cmd)), rl_clear_history(), 1);

			}
			lstclear_cmd(&(data->cmd));
		}
	}
	return (rl_clear_history(), 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		pid;
	int		res;

	pid = fork();
	if (!pid)
	{
		data = init_data(env);
		if (!data)
			return (1);
		loop_read(data);
		free_data(data);
	}
	else
	{
		signal(SIGINT, get_sig_parent);
		signal(SIGQUIT, get_sig_parent);
		wait(&res);
		printf("\n");
	}
	(void)ac;
	(void)av;
	return (0);
}
