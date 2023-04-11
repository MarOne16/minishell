/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listtools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:49:29 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/10 01:22:01 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prc	*ft_lstnewallcmd(char *allcmd, t_cmd *cmd)
{
	t_prc	*node;

	node = (t_prc *)malloc(sizeof(*node));
	if (!node)
		return (0);
	node->cmd = cmd;
	node->allcmd = allcmd;
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

void	ft_lstadd_frontcmd(t_prc **lst, t_prc *new)
{
	if (lst && new)
	{
		new -> next = *lst;
		*lst = new;
	}
}

t_prc	*ft_lstlastallcmd(t_prc *lst)
{
	t_prc	*l;

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

int	ft_lstsizetprc(t_prc *lst)
{
	t_prc	*l;
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

void	ft_lstadd_backallcmd(t_prc **lst, t_prc *new)
{
	t_prc	*lst2;

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