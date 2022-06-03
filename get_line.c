/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:55 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/03 16:34:37 by adesgran         ###   ########.fr       */
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
	t_env	*home;

	cwd = malloc(sizeof(char) * 1001);
	if (!getcwd(cwd, 1000))
		return (free(cwd), NULL);
	home = get_var_env(data->env, "HOME");
	if (home && ft_strncmp(home->value, cwd, ft_strlen(home->value)) == 0)
		cwd = replace_begin(data, cwd);
	if (ft_atoi(data->last_cmd_status))
		res = ft_strjoinx(7, COL_RED, BOLD, "minishell$> ", COL_YEL, cwd,
				COL_DEFAULT, "$ ");
	else
		res = ft_strjoinx(7, COL_BLU, BOLD, "minishell$> ", COL_YEL, cwd,
				COL_DEFAULT, "$ ");
	free(cwd);
	if (!res)
		res = ft_strjoinx(5, COL_RED, BOLD, "minishell$> ",	COL_DEFAULT, "$ ");
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
		printf("%sGood Bye!%s\n", COL_RED, COL_DEFAULT);
		return (NULL);
	}
	data->n_cmd++;
	if (line[0])
		add_history(line);
	return (line);
}
