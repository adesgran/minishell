/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 13:59:31 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	analyse_line(char *line, t_data *data)
{
	int		i;
	char	**line_tab;
	int		ret;

	ret = 1;
	line_tab = split_pipes(ft_strtrim(line, " \t\n\r\v\f"), &ret);
	free(line);
	if (!line_tab || ret == 2)
		return (ft_free_tabstr(line_tab), ret);
	i = 0;
	while (line_tab[i])
	{
		data->token = NULL;
		ret = lexer(line_tab[i], &data->token);
		if (ret)
			return (ft_free_tabstr(line_tab), ret);
		if (expander(data->token, data->env, data->last_cmd_status))
			return (lstclear_token(&data->token), ft_free_tabstr(line_tab), 1);
		if (token_to_cmd(data->token, &(data->cmd), data, i) == 1)
			return (lstclear_token(&data->token), ft_free_tabstr(line_tab), 1);
		lstclear_token(&data->token);
		i++;
	}
	return (ft_free_tabstr(line_tab), 0);
}

static char	*replace_begin(t_data *data, char *str)
{
	int		len;
	char	*usrdir;
	char	*res;
	int		i;
	int		j;

	usrdir = get_var_env(data->env, "HOME")->value;
	len = ft_strlen(str) - ft_strlen(usrdir) + 1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (str);
	i = ft_strlen(usrdir);
	j = 1;
	res[0] = '~';
	while (j < len && str[i])
	{
		res[j] = str[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (free(str), res);
}

static char	*get_prompt(t_data *data)
{
	char	*cwd;
	char	*res;
	char	*home;

	cwd = ft_calloc(sizeof(char), 201);
	if (!getcwd(cwd, 200))
		return (free(cwd), NULL);
	if (!get_var_env(data->env, "HOME"))
		return (ft_strdup(""));
	home = get_var_env(data->env, "HOME")->value;
	if (ft_strncmp(home, cwd, ft_strlen(home)) == 0)
		cwd = replace_begin(data, cwd);
	if (ft_atoi(data->last_cmd_status))
		res = ft_strjoinx(3, "\x1B[31m\033[1mminishell$> \x1B[33m",  cwd, "\x1B[0m$ ");
	else
		res = ft_strjoinx(3, "\x1B[34m\033[1mminishell$> \x1B[33m",  cwd, "\x1B[0m$ ");
	free(cwd);
	return (res);
}

static int	loop_read(t_data *data)
{
	char	*line;
	char	*prompt;
	int		ret;

	printf("\x1B[32mWelcome to Minishell!\x1B[0m\n");
	while (1)
	{
		signal(SIGINT, get_sig_child);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt(data);
		if (!prompt)
			prompt = ft_strjoinx(3, "\x1B[34m\033[1mminishell$> \x1B[33m",  get_var_env(data->env, "PWD")->value, "\x1B[0m$ ");
		if (!prompt)
		{
			printf("Prompt Malloc error\n");
			return (1);
		}
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			if (!line)
				printf("exit\n");
			printf("\x1B[31mGood Bye!\x1B[0m\n");
			return (rl_clear_history(), free(line), 0);
		}
		data->n_cmd++;
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

	res = 0;
	pid = fork();
	if (!pid)
	{
		data = init_data(env);
		if (!data)
			return (1);
		loop_read(data);
		free_data(data);
		exit(1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &res, 0);
		printf("\n");
		exit(res / 256);
	}
	(void)ac;
	(void)av;
	return (0);
}
