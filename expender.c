/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:25:04 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/19 19:09:47 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*replace_var_by_value(char *str, int *i, int len, t_env *env)
{
	char	*tmp;
	char	*dest;

	tmp = ft_substr(str, 0, *i);
	if (!tmp)
		return (NULL);
	*i += len;
	dest = ft_strjoinx(3, tmp, env->value, &str[*i]);
	free(tmp);
	if (!dest)
		return (NULL);
	free(str);
	return (dest);
}

char	*get_var_value(char *str, int *i, t_env *env)
{
	int		len;
	char	*var_name;

	len = 1;
	while (str[*i + len] && !ft_ischarset(str[*i + len], " \t\n\r\v\f\'\"$"))
		len++;
	var_name = ft_substr(str, *i, len);
	if (!var_name)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(&var_name[1], env->var) == 0)
			break ;
		env = env->next;
	}
	free(var_name);
	if (env)
		str = replace_var_by_value(str, i, len, env);
	return (str);
}

char	*lf_var(char *token, t_env *env)
{
	int	i;
	int	expend;

	i = 0;
	expend = 1;
	while (token[i])
	{
		if (token[i] == '\'')
			i++;
		else if (token[i] == '\'' && expend == 1)
			expend = 0;
		else if (token[i] == '\'' && expend == 0)
			expend = 1;
		else if (token[i] == '$' && expend == 1)
		{
			printf("	on trouve un $ en i = %d\n", i);
			token = get_var_value(token, &i, env);
			if (!token)
				return (NULL);
		}
		if (!token[i])
			break ;
		i++;
	}
	return (token);
}

int	expender(t_token *token, t_env *env)
{
	char	*str;

	while (token)
	{
		token->token = lf_var(token->token, env);
		str = ft_remove_quotes(token->token);
		if (!str)
			return (1);
		free(token->token);
		token->token = str;
		token = token->next;
	}
	return (0);
}
