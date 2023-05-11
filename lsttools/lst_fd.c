/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:37:13 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/27 15:08:00 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_fd	*ft_lstlast_fd(t_fd *lst)
{
	t_fd	*l;

	if (!lst)
		return (0x0);
	l = lst;
	while (l -> next != 0)
	{
		l = l -> next;
	}
	return (l);
}

void	ft_lstadd_back_fd(t_fd **lst, t_fd *new)
{
	t_fd	*lst2;

	if (lst == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		lst2 = ft_lstlast_fd(*lst);
		lst2 -> next = new;
		new -> previus = lst2;
	}
}

void	ft_lstadd_front_fd(t_fd **lst, t_fd *new)
{
	if (lst && new)
	{
		new -> next = *lst;
		*lst = new;
	}
}

t_fd	*ft_lstnew_fd(char type, int fd)
{
	t_fd	*node;

	node = (t_fd *)ft_malloc(sizeof(*node), 1);
	if (!node)
		return (0);
	node->type = type;
	node->fd = fd;
	node->next = 0;
	node->previus = 0;
	return (node);
}
