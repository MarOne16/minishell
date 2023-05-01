/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:58:14 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/29 19:01:29 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

t_my_list	*ft_my_lstnew(char *name, char *value)
{
	t_my_list	*new;

	new = (t_my_list *)malloc(sizeof(t_my_list));
	if (!new)
		return (0);
	if (!name && !value)
		return (0);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_my_lstsize(t_my_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_my_list	*ft_my_lstlast(t_my_list *lst)
{
	t_my_list	*l;

	l = lst;
	if (!lst)
		return (0x0);
	l = lst;
	while (l->next != 0)
	{
		l = l->next;
	}
	return (l);
}

void	ft_my_lstadd_back(t_my_list **lst, t_my_list *new)
{
	t_my_list	*lst2;

	if (lst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
	}
	else
	{
		lst2 = ft_my_lstlast(*lst);
		lst2->next = new;
	}
}

int	size_prc(t_exe *allcmd)
{
	int		i;
	t_exe	*tmp;

	i = 0;
	tmp = allcmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
