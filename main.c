/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/04 15:32:34 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	g_gbg;

void	free_tab_token(void)
{
	int	i;

	i = 0;
	while (g_gbg.tab_token[i])
	{
		lstclear_token(&g_gbg.tab_token[i]);
		i++;
	}
	free(g_gbg.tab_token);
}

void	free_garbage(void)
{
	free_data(g_gbg.data);
	ft_free_tabstr(g_gbg.line_tab);
	free_tab_token();
	free(g_gbg.heredoc_name);
	close(g_gbg.fd_heredoc);
}

int	init_tab_token(t_data *data, char *line)
{
	int	len;
	int	i;
	int	ret;

	ret = 1;
	g_gbg.line_tab = split_pipes(ft_strtrim(line, " \t\n\r\v\f"), &ret);
	free(line);
	if (!g_gbg.line_tab || ret == 2)
		return (ft_free_tabstr(g_gbg.line_tab), ret);
	len = ft_tablen(g_gbg.line_tab);
	g_gbg.tab_token = malloc(sizeof(t_token *) * (len + 1));
	if (!g_gbg.tab_token)
		return (ft_free_tabstr(g_gbg.line_tab), 1);
	i = -1;
	while (++i <= len)
		g_gbg.tab_token[i] = NULL;
	i = 0;
	while (i < len)
	{
		ret = lexer(data, g_gbg.line_tab[i], &g_gbg.tab_token[i], i);
		if (ret)
			return (ft_free_tabstr(g_gbg.line_tab), free_tab_token(), ret);
		i++;
	}
	return (ft_free_tabstr(g_gbg.line_tab), 0);
}

static int	analyse_line(char *line, t_data *data)
{
	int			i;
	int			ret;

	ret = init_tab_token(data, line);
	if (ret)
		return (ret);
	i = 0;
	while (g_gbg.tab_token[i])
	{
		if (expander(g_gbg.tab_token[i], data->env, data->last_cmd_status))
			return (free_tab_token(), 1);
		ret = token_to_cmd(g_gbg.tab_token[i], data, i);
		if (ret)
			return (free_tab_token(), ret);
		i++;
	}
	return (free_tab_token(), 0);
}

static int	execution(t_data *data)
{
	int	ret;

	if (get_bin_path(data->cmd, get_path(data)) == 1)
		return (1);
	if (is_env_built_in(data->cmd))
		ret = env_built_in(data, data->cmd);
	else
		ret = pipex(data, data->cmd);
	if (ret == -1)
		return (1);
	free(data->last_cmd_status);
	data->last_cmd_status = ft_itoa(ret);
	if (!data->last_cmd_status)
		return (1);
	return (0);
}

static void	loop_read(t_data *data)
{
	char	*line;
	int		ret;

	while (1)
	{
		signal(SIGINT, get_sig_child);
		signal(SIGQUIT, SIG_IGN);
		line = get_line(data);
		signal(SIGINT, SIG_IGN);
		if (!line)
			return (rl_clear_history());
		if (line[0])
		{
			ret = analyse_line(line, data);
			if (ret == 1)
				return (rl_clear_history());
			if (ret == 0)
				if (execution(data) == 1)
					return (rl_clear_history());
			lstclear_cmd(&(data->cmd));
		}
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		pid;
	int		res;

	res = 0;
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (1);
	pid = fork();
	if (!pid)
	{
		data = init_data(env);
		if (!data)
			return (1);
		printf("\x1B[32mWelcome to Minishell!\x1B[0m\n");
		loop_read(data);
		free_data(data);
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &res, 0);
	printf("\n");
	(void)ac;
	(void)av;
	return (close(1), close(2), close(3), res / 256);
}
