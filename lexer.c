/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:41:02 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/12 15:23:40 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len_token(char *str)
{
	int		len;
	char	quote;
	int		nb_quote;

	len = 0;
	quote = 0;
	if (str[len] == '\'' || str[len] == '\"')
	{
		quote = str[len];
		while (quote && str[len] == quote)
			len++;
		nb_quote = len;
		while (str[len] && str[len] != quote)
			len++;
		while (nb_quote > 0 && str[len] && str[len] == quote)
		{
			len++;
			nb_quote--;
		}
	}
	else
	{
		while (str[len] && str[len] != '<' && str[len] != '>' && str[len] != quote
			&& str[len] != ' ' && (str[len] < 9 || str[len] > 13))
		{
			if (str[len] == '\\')
				len++;
			len++;
		}
	}
	// printf("on fini a str[%d] = %c avec %d quotes\n", len, str[len], nb_quote);
	if (nb_quote != 0)
		return (ft_putstr_fd("Error: open quote\n", 2), -1);
	return (len);
}

t_token	*new_word(char *str, int *i, int type_word)
{
	int		len;
	char	*new_str;
	t_token	*new;

	len = len_token(&str[*i]);
	// len = 0;
	// while (str[*i + len] && str[*i + len] != '<' && str[*i + len] != '>'
	// 	&& str[*i + len] != ' ' && (str[*i + len] < 9 || str[*i + len] > 13))
	// 	len++;
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	new = lstnew_token(new_str, type_word); // protection malloc
	printf("	** new token = %s de type %d **\n", new_str, type_word);
	return (new);
	// lstadd_back_token(token, new);
}

t_token	*new_outfile(char *str, int *i, int type)
{
	char	*new_str;
	int		len;
	t_token	*new;

	(*i)++;
	if (str[*i] == '>')
	{
		type = GREATGREAT;
		(*i)++;
	}
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), NULL);
	len = len_token(&str[*i]);
	// len = 0;
	// while (str[*i + len] && str[*i + len] != '<' && str[*i + len] != '>'
	// 	&& str[*i + len] != ' ' && (str[*i + len] < 9 || str[*i + len] > 13))
	// 	len++;
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	new = lstnew_token(new_str, type); // protection malloc
	printf("	** new token = %s de type %d **\n", new_str, type);
	return (new);
	// lstadd_back_token(token, new);
}

t_token	*new_infile(char *str, int *i, int type)
{
	char	*new_str;
	int		len;
	t_token	*new;

	(*i)++;
	if (str[*i] == '<')
	{
		type = HEREDOC;
		(*i)++;
	}
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), NULL);
	len = len_token(&str[*i]);
	if (len == -1)
		return (NULL);
	// len = 0;
	// while (str[*i + len] && str[*i + len] != '<' && str[*i + len] != '>'
	// 	&& str[*i + len] != ' ' && (str[*i + len] < 9 || str[*i + len] > 13))
	// 	len++;
	new_str = ft_substr(str, *i, len);
	if (!new_str)
		return (NULL);
	*i += len - 1;
	new = lstnew_token(new_str, type); // protection malloc
	printf("	** new token = %s de type %d **\n", new_str, type);
	return (new);
	// lstadd_back_token(token, new);
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
				new = new_infile(str, &i, LESS);
			else if (str[i] == '>')
				new = new_outfile(str, &i, GREAT);
			else
				new = new_word(str, &i, WORD);
			if (!new)
				return ;
			lstadd_back_token(token, new);
		}
		i++;
	}
	printf("fin lexer\n");
}
