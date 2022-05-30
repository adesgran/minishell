/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/30 13:06:17 by adesgran         ###   ########.fr       */
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
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)sig;
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
		if (token_to_cmd(token, &(data->cmd), data, i) == 1)
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
		line = readline(ft_strjoinx(3, "\x1B[34m\033[1mminishell$> \x1B[33m",  get_var_env(data->env, "PWD")->value, "\x1B[0m$ "));
		if (!line)
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
			if (ret == 0)
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
	data = init_data(env);
	if (!data)
		return (1);
	if (!pid)
	{
		loop_read(data);
		free_data(data);
	}
	else
	{
		signal(SIGINT, get_sig_parent);
		signal(SIGQUIT, get_sig_parent);
		wait(&res);
		free_data(data);
		printf("\n");
	}
	(void)ac;
	(void)av;
	return (0);
}
