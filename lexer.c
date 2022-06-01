/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:41:02 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/01 12:06:26 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	syntax_error(char c, int *ret)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (c)
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	*ret = 2;
}

static int	len_token(char *str, int i, int *ret)
{
	char	quote;

	if (i == -1 || !str[i] || ft_ischarset(str[i], "<> \t\n\r\v\f|"))
		return (i);
	quote = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i++];
		while (str[i] && str[i] != quote)
			if (str[i++] == '\\' && str[i])
				i++;
		if (str[i++] != quote)
			return (syntax_error('\0', ret), -1);
	}
	else
	{
		while (str[i] && !ft_ischarset(str[i], "<>\'\" \t\n\r\v\f|"))
			if (str[i++] == '\\' && str[i])
				i++;
	}
	return (len_token(str, i, ret));
}

static t_token	*new_word(char *str, int *i, int type_word, int *ret)
{
	int		len;
	char	*new_str;

	len = len_token(&str[*i], 0, ret);
	if (len == -1)
		return (NULL);
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	return (lstnew_token(new_str, type_word));
}

static t_token	*new_file(char *str, int *i, char chevron, int *ret)
{
	char	*new_str;
	int		len;
	int		type;

	if (str[++(*i)] == chevron)
	{
		type = chevron + 1;
		(*i)++;
	}
	else
		type = chevron;
	while (ft_ischarset(str[*i], " \t\n\r\v\f"))
		(*i)++;
	if (!str[*i] || ft_ischarset(str[*i], "<>|"))
		return (syntax_error(str[*i], ret), NULL);
	len = len_token(&str[*i], 0, ret);
	if (len == -1)
		return (NULL);
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	return (lstnew_token(new_str, type));
}

int	lexer(char *str, t_token **token)
{
	int		i;
	int		ret;
	t_token	*new;

	i = 0;
	ret = 0;
	while (str[i] && str[i] != '|')
	{
		if (!ft_ischarset(str[i], " \t\n\r\v\f"))
		{
			if (str[i] == '<')
				new = new_file(str, &i, '<', &ret);
			else if (str[i] == '>')
				new = new_file(str, &i, '>', &ret);
			else
				new = new_word(str, &i, WORD, &ret);
			if (!new)
				return (lstclear_token(token), ret);
			lstadd_back_token(token, new);
		}
		i++;
	}
	if (str[i] == '|' && !*token)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), 2);
	return (ret);
}
