/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:25:04 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/04 17:28:32 by mchassig         ###   ########.fr       */
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
	int		i;
	bool	is_expandable;
	int		ret;

	i = 0;
	is_expandable = TRUE;
	ret = 0;
	while (token[0][i])
	{
		if (token[0][i] == '\\')
			i++;
		else if (!is_heredoc && token[0][i] == '\'')
			is_expandable = !is_expandable;
		else if (token[0][i] == '$' && is_expandable == TRUE)
		{
			ret = 1;
			token[0] = get_var_value(token[0], &i, env, last_cmd_status);
			if (!token[0])
				return (-1);
		}
		if (token[0][i])
			i++;
	}
	return (ret);
}

int	replace_token(t_token **token)
{
	char	**tab_str;
	int		i;
	t_token	*new;

	tab_str = ft_split((*token)->token, ' ');
	if (!tab_str)
		return (1);
	free((*token)->token);
	i = -1;
	(*token)->token = tab_str[++i];
	while (tab_str[++i])
	{
		new = lstnew_token(tab_str[i], WORD);
		if (!new)
			return (ft_free_tabstr(tab_str), 1);
		new->next = (*token)->next;
		(*token)->next = new;
		*token = (*token)->next;
	}
	return (free(tab_str), 0);
}

int	expander(t_token *token, t_env *env, char *last_cmd_status)
{
	int		is_expanded_quote;

	while (token)
	{
		if (token->type != HEREDOC)
		{
			token->unexpanded = ft_strdup(token->token);
			if (!token->unexpanded)
				return (1);
			token->expanded = lf_var(&(token->token), env, last_cmd_status, 0);
			if (token->expanded == -1)
				return (1);
			is_expanded_quote = ft_remove_quotes(token);
			if (is_expanded_quote == -1)
				return (1);
			if (token->type == WORD && token->token[0] && !is_expanded_quote)
				if (replace_token(&token) == 1)
					return (1);
		}
		token = token->next;
	}
	return (0);
}
