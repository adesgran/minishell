/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:25:04 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/23 14:43:20 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*replace_var_by_value(char *str, int *i, int len, char *value)
{
	char	*tmp;
	char	*dest;

	tmp = ft_substr(str, 0, *i);
	if (!tmp)
		return (NULL);
	*i += len;
	dest = ft_strjoinx(3, tmp, value, &str[*i]);
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
	while (str[*i + len] && (ft_isalnum(str[*i + len]) || str[*i + len] == '_'))
		len++;
	var_name = ft_substr(str, *i, len);
	if (!var_name)
		return (NULL);
	while (env && ft_strcmp(&var_name[1], env->var) != 0)
		env = env->next;
	free(var_name);
	if (env)
		str = replace_var_by_value(str, i, len, env->value);
	else
		str = replace_var_by_value(str, i, len, "");
	return (str);
}

char	*lf_var(char *token, t_env *env)
{
	int	i;
	int	expand;

	i = 0;
	expand = 1;
	while (token[i])
	{
		if (token[i] == '\'')
			i++;
		else if (token[i] == '\'' && expand == 1)
			expand = 0;
		else if (token[i] == '\'' && expand == 0)
			expand = 1;
		else if (token[i] == '$' && expand == 1)
		{
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

int	replace_token(t_token **token, char *str)
{
	char	**tab_str;
	int		i;
	t_token	*new;

	tab_str = ft_split(str, ' ');
	free(str);
	if (!tab_str)
		return (1);
	i = 0;
	free((*token)->token);
	(*token)->token = tab_str[i++];
	while (tab_str[i])
	{
		new = lstnew_token(tab_str[i], WORD);
		if (!new)
			return (ft_free_tabstr(tab_str), 1);
		new->next = (*token)->next;
		(*token)->next = new;
		*token = (*token)->next;
		i++;
	}
	return (free(tab_str), 0);
}

int	expander(t_token *token, t_env *env)
{
	char	*str;

	while (token)
	{
		token->token = lf_var(token->token, env);
		str = ft_remove_quotes(token->token);
		if (!str)
			return (1);
		if (token->type != WORD || !str[0])
		{
			free(token->token);
			token->token = str;
		}
		else if (replace_token(&token, str) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}
