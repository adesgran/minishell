/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:30:53 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/04 17:48:20 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(*str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
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
			free(varname);
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
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		free(varname);
		return (1);
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
