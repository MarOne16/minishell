/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_all_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:39:55 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/27 17:03:16 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exe	*ft_lstnewallcmd(void **cmd, void *fd)
{
	t_exe	*node;

	node = (t_exe *)ft_malloc(sizeof(*node));
	if (!node)
		return (0);
	node->lakher = cmd;
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
