/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:04:50 by mqaos             #+#    #+#             */
/*   Updated: 2022/11/09 19:01:55 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst2;

	if (lst == 0)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		lst2 = ft_lstlast(*lst);
		lst2 -> next = new;
	}
}
// int main()
// {
// 	t_list	*root;
// 	t_list	*root2;
// 	root = ft_lstnew("hi");
// 	root2 = ft_lstnew("maro");
// 	root->next = root2;
// 	ft_lstadd_back(root,ft_lstnew("ok"));
// 	return 0;
// }