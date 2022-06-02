/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:30:53 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 18:21:42 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(*str))
	{
		printf("minishell: export: `%s\': not a valid identifier\n", str);
		return (NULL);
	}
	while ((ft_isalnum(str[i]) || str[i] == '_') && str[i])
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strndup(str, i));
}

static void	set_env_value(t_data *data, char *str, char *varname)
{
	t_env	*env;
	char	*var;

	var = ft_strdup(str + ft_strlen(varname) + 1);
	if (!var)
		return ;
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

static int	mini_export_loop(t_data *data, char *str)
{
	char	*varname;
	int		i;

	if (!str || !*str)
		return (0);
	varname = get_var_name(str);
	if (!varname || !*varname || !ft_strcmp(varname, "_"))
		return (0);
	i = ft_strlen(varname);
	if (str[i] == '\0')
		return (free(varname), 0);
	else if (ft_strncmp(str + i, "+=", 2) == 0)
		append_env_value(data, str, varname);
	else if (str[i] == '=')
		set_env_value(data, str, varname);
	else
	{
		free(varname);
		return (2);
	}
	return (0);
}

int	mini_export(t_data *data, char **cmd)
{
	int	res;

	res = 0;
	if (!data || !cmd)
		return (1);
	cmd++;
	if (!*cmd)
		return (export_empty(data), 0);
	while (*cmd)
	{
		res = mini_export_loop(data, *cmd);
		cmd++;
	}
	return (res);
}
