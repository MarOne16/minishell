/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listtools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:49:29 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 15:27:30 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	*ft_lstnewallcmd(void **cmd, void *fd)
{
	t_exe	*node;

	node = (t_exe *)malloc(sizeof(*node));
	if (!node)
		return (0);
	node->lakher = cmd;
	node->fd = fd;
	node-> next = 0;
	node-> previus = 0;
	return (node);
}

t_fd	*ft_lstnew_fd(char type, int fd)
{
	t_fd	*node;

	node = (t_fd *)malloc(sizeof(*node));
	if (!node)
		return (0);
	node->type = type;
	node->fd = fd;
	node-> next = 0;
	node-> previus = 0;
	return (node);
}

t_cmd	*ft_lstnewcmd(char *cmd, int type)
{
	t_cmd	*newcmd;

	newcmd = malloc(sizeof(t_cmd));
	if (!newcmd)
		return (NULL);
	newcmd->type = type;
	newcmd->cmd = cmd;
	newcmd->next = NULL;
	newcmd->previus = NULL;
	return (newcmd);
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

// t_fd
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