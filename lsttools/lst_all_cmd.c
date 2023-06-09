/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_all_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:39:55 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/16 16:53:01 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exe	*ft_lstnewallcmd(char **cmd, void *fd)
{
	t_exe	*node;

	node = (t_exe *)ft_malloc(sizeof(*node), 1);
	if (!node)
		return (0);
	node->last = cmd;
	node->fd = fd;
	node->next = 0;
	node->previus = 0;
	return (node);
}

void	ft_lstadd_frontcmd(t_exe **lst, t_exe *new)
{
	if (lst && new)
	{
		new -> next = *lst;
		*lst = new;
	}
}

t_exe	*ft_lstlastallcmd(t_exe *lst)
{
	t_exe	*l;

	if (!lst)
		return (0x0);
	l = lst;
	while (l -> next != 0)
	{
		l = l -> next;
	}
	return (l);
}

void	ft_lstadd_backallcmd(t_exe **lst, t_exe *new)
{
	t_exe	*lst2;

	if (lst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
	}
	else
	{
		lst2 = ft_lstlastallcmd(*lst);
		lst2 -> next = new;
		new -> previus = lst2;
	}
}
