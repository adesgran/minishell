/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:10:10 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/03 12:20:54 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_size_inquotes(char *str, int *i, int *res)
{
	char	sep;

	sep = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != sep)
	{
		if (str[*i] == '\\' && str[*i + 1] == sep)
			*i += 2;
		else
			*i += 1;
		*res += 1;
	}
	*i += 1;
	return (0);
}

static int	get_size(char *str, t_token *token)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			res++;
		}
		else if (str[i] == '\"' || str[i] == '\'')
		{
			get_size_inquotes(str, &i, &res);
			if (token->type == HEREDOC)
				token->expanded = 1;
		}
		else
		{
			i++;
			res++;
		}
	}
	return (res);
}

static void	fill_str_inquotes(char **res, char **str)
{
	char	sep;

	sep = **str;
	*str += 1;
	while (**str && **str != sep)
	{
		if (str[0][0] == '\\' && str[0][1] == sep)
		{
			res[0][0] = str[0][1];
			*res += 1;
			*str += 2;
		}
		else
		{
			res[0][0] = str[0][0];
			*res += 1;
			*str += 1;
		}
	}
	*str += 1;
}

static void	fill_str(char *res, char *str)
{
	while (*str)
	{
		if (str[0] == '\\' && str[1])
		{
			*res = str[1];
			str += 2;
			res++;
		}
		else if (*str == '\"' || *str == '\'')
			fill_str_inquotes(&res, &str);
		else
		{
			*res = *str;
			res++;
			str++;
		}
	}
	*res = '\0';
}

int	ft_remove_quotes(t_token *token)
{
	size_t	size;
	char	*res;
	int		is_expanded_quote;

	is_expanded_quote = 0;
	size = get_size(token->token, token);
	if (size != ft_strlen(token->token))
		is_expanded_quote = 1;
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (-1);
	fill_str(res, token->token);
	free(token->token);
	token->token = res;
	return (is_expanded_quote);
}
