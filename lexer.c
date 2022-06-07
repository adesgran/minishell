/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:41:02 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/07 18:31:49 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	g_gbg;

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
			if (str[i++] == '\\' && str[i])
				i++;
		if (str[i++] != quote)
			return (syntax_error('\0'), -1);
	}
	else
	{
		while (str[i] && !ft_ischarset(str[i], "<>\'\" \t\n\r\v\f|"))
			if (str[i++] == '\\' && str[i])
				i++;
	}
	return (len_token(str, i));
}

static int	add_token(char *str, int *i, int type, t_token **token)
{
	int		len;
	char	*new_str;
	t_token	*new;

	len = len_token(&str[*i], 0);
	if (len == -1)
		return (2);
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (1);
	*i += len - 1;
	new = lstnew_token(new_str, type);
	if (!new)
		return (1);
	lstadd_back_token(token, new);
	return (0);
}

static int	new_file(char *str, int *i, char chevron, t_token **token)
{
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
	if (!str[*i] || ft_ischarset(str[*i], "<>"))
		return (syntax_error(str[*i]), 2);
	return (add_token(str, i, type, token));
}

int	lexer(t_data *data, char *str, t_token **token, int num)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i] && str[i] != '|')
	{
		if (!ft_ischarset(str[i], " \t\n\r\v\f"))
		{
			if (str[i] == '<' || str[i] == '>')
				ret = new_file(str, &i, str[i], token);
			else
				ret = add_token(str, &i, WORD, token);
			if (ret)
				return (ret);
			if (lstlast_token(*token)->type == HEREDOC)
				ret = create_heredoc(data, lstlast_token(*token), num);
			if (ret)
				return (lstclear_token(token), ret);
		}
		i++;
	}
	if (str[i] == '|' && !g_gbg.line_tab[num + 1])
		return (syntax_error(str[i]), 2);
	return (ret);
}
