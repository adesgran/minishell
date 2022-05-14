/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:53:52 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/14 15:09:34 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_CMD_H
# define LST_CMD_H

typedef struct s_cmd
{
	char			**cmd;
	char			*bin_path;
	int				fd_infile;
	int				*fd_outfile;
	int				nb_outfile;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*lstnew_cmd(void);
void	lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void	lstclear_cmd(t_cmd **lst);
void	lstdelone_cmd(t_cmd *lst);
t_cmd	*lstlast_cmd(t_cmd *lst);

#endif