/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:30:53 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/17 14:27:26 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	while ((ft_isalnum(*str) || *str == '_') && str[i])
		i++;
	if (!str[i])
		return (ft_strdup("_"));
	return (ft_strndup(str, i));
}

/*static int	check_varname(char *str)
{
	if (ft_isalnum(*str) == 0 && *str != '_')
		return (1);
	while (*str)
	{
		if (ft_isalnum(*str) == 0 && *str != '_')
			return (1);
		str++;
	}
	return (0);
}*/

static void set_env_value(t_data *data, char *str, char *varname)
{
	t_env	*env;
	char	*var;

	var = ft_remove_quotes(str + ft_strlen(varname) + 1);
	if (!var)
		return ;
	if (!*var)
		return (free(var));
	env = get_var_env(data->env, varname);
	if (env)
	{
		if (env->value)
			free(env->value);
		env->value = var;
	}
	else
		push_back_env(data->env, varname, var);
}

static void	append_env_value(t_data *data, char *str, char *varname)
{
	t_env	*env;
	char	*var;
	char	*temp;

	var = ft_strdup(str + ft_strlen(varname) + 2);
	if (!var)
		return ;
	env = get_var_env(data->env, varname);
	if (env)
	{
		if (env->value)
		{
			temp = env->value;
			env->value = ft_strjoin(temp, var);
			free(var);
			free(temp);
		}
		else
			env->value = var;
	}
	else
		push_back_env(data->env, varname, var);
}
	

int	mini_export(t_data *data, char *str)
{
	char	*varname;
	int		i;

	if (!str || !*str)
		return (0);
	varname = get_var_name(str);
	if (!varname  || !*varname)
		return (0);
	i = ft_strlen(varname);
	if (str[i] == '\0')
		return (0);
	else if (str[i] == '=')
		set_env_value(data, str, varname);
	else if (ft_strncmp(str + i, "+=", 2))
		append_env_value(data, str, varname);
	else
	{
		printf("minishell: %d: export: %s: bad variable name", data->n_cmd, varname);
		free(varname);
		return (2);
	}
	return (0);
}
