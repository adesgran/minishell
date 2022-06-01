/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:25:04 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/01 11:24:47 by mchassig         ###   ########.fr       */
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
	dest = ft_strjoinx(3, tmp, value, &str[*i + len]);
	*i = *i + ft_strlen(value);
	if (ft_strlen(value) > 0)
		(*i)--;
	free(tmp);
	if (!dest)
		return (NULL);
	free(str);
	return (dest);
}

char	*get_var_value(char *str, int *i, t_env *env, char *last_cmd_status)
{
	int		len;
	char	*var_name;

	len = 1;
	if (str[*i + 1] == '?')
		len++;
	else
		while (str[*i + len] && (ft_isalnum(str[*i + len]) || \
					str[*i + len] == '_'))
			len++;
	var_name = ft_substr(str, *i, len);
	if (!var_name)
		return (NULL);
	env = get_var_env(env, &var_name[1]);
	if (ft_strcmp(var_name, "$?") == 0)
		str = replace_var_by_value(str, i, len, last_cmd_status);
	else if (env)
		str = replace_var_by_value(str, i, len, env->value);
	else
		str = replace_var_by_value(str, i, len, "");
	return (free(var_name), str);
}

int	lf_var(char **token, t_env *env, char *last_cmd_status, int is_heredoc)
{
	int	i;
	int	expand;
	int	ret;
	
	i = 0;
	expand = 1;
	ret = 0;
	while (token[0][i])
	{
		if (token[0][i] == '\\')
			i++;
		else if (!is_heredoc && token[0][i] == '\'' && expand == 1)
			expand = 0;
		else if (!is_heredoc && token[0][i] == '\'' && expand == 0)
			expand = 1;
		else if (token[0][i] == '$' && expand == 1)
		{
			ret = 1;
			token[0] = get_var_value(token[0], &i, env, last_cmd_status);
			if (!token[0])
				return (-1);
		}
		if (!token[0][i])
			break ;
		i++;
	}
	return (ret);
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

int	expander(t_token *token, t_env *env, char *last_cmd_status)
{
	char	*str;

	while (token)
	{
		token->unexpanded = ft_strdup(token->token);
		if (!token->unexpanded)
			return (1);
		if (token->type != HEREDOC)
			token->expanded = lf_var(&(token->token), env, last_cmd_status, 0);
		if (token->expanded == -1)
			return (1);
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
