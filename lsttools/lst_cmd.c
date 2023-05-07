/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:49:29 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/27 15:08:00 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnewcmd(char *cmd, int type)
{
	t_cmd	*newcmd;

	newcmd = ft_malloc(sizeof(t_cmd));
	if (!newcmd)
		return (0);
	newcmd->type = type;
	newcmd->cmd = cmd;
	newcmd->next = 0;
	newcmd->previus = 0;
	return (newcmd);
}

t_cmd	*ft_lstlastcmd(t_cmd *lst)
{
	t_cmd	*l;

	if (!lst)
		return (0x0);
	l = lst;
	while (l -> next != 0)
	{
		l = l -> next;
	}
	return (l);
}

int	ft_lstsizetprc(t_cmd *lst)
{
	t_cmd	*l;
	int		i;

	if (!lst)
		return (0x0);
	l = lst;
	i = 0;
	while (l)
	{
		l = l -> next;
		i++;
	}
	return (i);
}

void	ft_lstadd_backcmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*lst2;

	if (lst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
	}
	else
	{
		lst2 = ft_lstlastcmd(*lst);
		lst2 -> next = new;
		new -> previus = lst2;
	}
}
