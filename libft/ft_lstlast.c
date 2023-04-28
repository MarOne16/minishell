/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:51:47 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/27 02:07:34 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*l;

	if (!lst)
		return (0x0);
	l = lst;
	while (l -> next != NULL)
	{
		l = l -> next;
	}
	return (l);
}
// #include<stdio.h>
// int main(int argc, char  *argv[])
// {
//     t_list *n1;
//     t_list *n2;
//     t_list *n3;
//     n1 =(t_list *)malloc(sizeof(t_list));
//     n2 =(t_list *)malloc(sizeof(t_list));
//     n3 =(t_list *)malloc(sizeof(t_list));
//     n1->next = n2;
//     n2->next = n3;
//     n3->next = 0;
//     n1 -> content ="1";
//     n2 -> content ="2";
//     n3 -> content ="3";
// 	printf("%s",ft_lstlast(n1)->content);
// 	return 0;
// }