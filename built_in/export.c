/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:30:53 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 13:27:18 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] != '=' || ft_strncmp(str + i, str[i])
		i++;
	return ft_strndup(str, i);
}

static int	check_varname(char *str)
{
	if (ft_isalnum(*str) == 0)
		return (1);
	while (*str)
	{
		if (ft_isalnum(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}

int	mini_export(t_data *data, char *str)
{
	char	*varname;
	int		i;

	varname = get_var_name(str);
	if (!varname  || !*varname)
	i = ft_strlen(varname);
	if (str[i] = '\0')
		return (0);
	else if (str[i] = '=')
		set_env_value(data, str);
	else if (ft_strncmp(str + i, "+=", 2))
		append_env_value(data, str + i + 2);
	else
	{
		printf("minishell: %d: export: %s: bad variable name", data->n_cmd, varname);
		free(varname);
		return (2);

