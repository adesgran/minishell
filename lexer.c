/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:41:02 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/24 17:50:46 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	len_token(char *str, int i)
{
	char	quote;

	if (i == -1 || !str[i] || ft_ischarset(str[i], "<> \t\n\r\v\f|"))
		return (i);
	quote = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i++];
		while (str[i] && str[i] != quote)
		{
			if (str[i] == '\\' && str[i + 1])
				i++;
			i++;
		}
		if (str[i++] != quote)
			return (ft_putstr_fd("Error: open quote\n", 2), -1);
	}
	else
	{
		while (str[i] && !ft_ischarset(str[i], "<>\'\" \t\n\r\v\f|"))
		{
			if (str[i] == '\\' && str[i + 1])
				i++;
			i++;
		}
	}
	return (len_token(str, i));
}

static t_token	*new_word(char *str, int *i, int type_word)
{
	int		len;
	char	*new_str;

	len = len_token(&str[*i], 0);
	if (len == -1)
		return (NULL);
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	return (lstnew_token(new_str, type_word));
}

static void	error_chevron(char c, int *ret)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (c)
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	*ret = 2;
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
		return (error_chevron(str[*i], ret), NULL);
	len = len_token(&str[*i], 0);
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
				new = new_word(str, &i, WORD);
			if (!new)
				return (lstclear_token(token), ret);
			lstadd_back_token(token, new);
		}
		i++;
	}
	return (ret);
}
