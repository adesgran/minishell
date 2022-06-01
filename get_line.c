/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:55 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 18:23:10 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

	cwd = malloc(sizeof(char) * 201);
	if (!getcwd(cwd, 200))
		return (free(cwd), NULL);
	if (!get_var_env(data->env, "HOME"))
		return (ft_strdup(""));
	home = get_var_env(data->env, "HOME")->value;
	if (ft_strncmp(home, cwd, ft_strlen(home)) == 0)
		cwd = replace_begin(data, cwd);
	if (ft_atoi(data->last_cmd_status))
		res = ft_strjoinx(3, "\x1B[31m\033[1mminishell$> \x1B[33m", cwd,
				"\x1B[0m$ ");
	else
		res = ft_strjoinx(3, "\x1B[34m\033[1mminishell$> \x1B[33m", cwd,
				"\x1B[0m$ ");
	free(cwd);
	if (!res)
		res = ft_strdup("\x1B[34m\033[1mminishell$> \x1B[33m\x1B[0m$ ");
	return (res);
}

char	*get_line(t_data *data)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt(data);
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		printf("exit\n");
		printf("\x1B[31mGood Bye!\x1B[0m\n");
		return (NULL);
	}
	data->n_cmd++;
	if (line[0])
		add_history(line);
	return (line);
}
