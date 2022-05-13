/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:41:02 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 18:47:24 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len_token(char *str, int i)
{
	char	quote;

	if (!str[i] || str[i] == '<' || str[i] == '>'
		|| str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		return (i);
	quote = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i++];
		while (str[i] && str[i] != quote)
			i++;
		if (str[i++] != quote)
			return (ft_putstr_fd("Error: open quote\n", 2), -1);
	}
	else
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '\''
			&& str[i] != '\"' && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
		{
			if (str[i] == '\\')
				i++;
			i++;
		}
	}
	return (len_token(str, i));
}

t_token	*new_word(char *str, int *i, int type_word)
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

void	error_chevron(char chevron)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putchar_fd(chevron, 2);
	ft_putstr_fd("'\n", 2);
}

t_token	*new_file(char *str, int *i, int type, char chevron)
{
	char	*new_str;
	int		len;

	(*i)++;
	if (str[*i] == chevron)
	{
		type++;
		(*i)++;
	}
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
		return (error_chevron(chevron), NULL);
	len = len_token(&str[*i], 0);
	if (len == -1)
		return (NULL);
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	return (lstnew_token(new_str, type));
}

void	lexer(char *str, t_token **token)
{
	int		i;
	t_token	*new;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || (str[i] < 9 && str[i] > 13))
		{
			if (str[i] == '<')
				new = new_file(str, &i, LESS, '<');
			else if (str[i] == '>')
				new = new_file(str, &i, GREAT, '>');
			else
				new = new_word(str, &i, WORD);
			if (!new)
				return (lstclear_token(token));
			lstadd_back_token(token, new);
		}
		i++;
	}
}
