/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:15:34 by mqaos             #+#    #+#             */
/*   Updated: 2022/11/10 18:16:04 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*root;

	if (lst == 0x0 || f == 0x0 || del == 0x0)
		return (0x0);
	root = 0;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&root, del);
			return (0);
		}
		ft_lstadd_back(&root, new);
		lst = lst->next;
	}
	return (root);
}

// #include<stdio.h>
// void d(void *c)
// {
// 	free(c);
// }

// void *test(void *c)
// {
// 	char *p  = (char *)c;
// 	int i = 0;
// 	while (p[i])
// 	{
// 		p[i] -=32;
// 		i++;
// 	}
// 	return (p);
// }

// 	int    main(void)
// 	{
// 	t_list    *head;
// 	t_list    *node1;
// 	t_list    *node2;
// 	int			i = 0;

// 	char    *s1 = ft_strdup("a");
// 	char    *s2 = ft_strdup("b");
// 	char    *s3 = ft_strdup("c");

// 	head = NULL;
// 	ft_lstadd_front(&head, ft_lstnew(s1));
// 	ft_lstadd_front(&head, ft_lstnew(s2));
// 	ft_lstadd_back(&head, ft_lstnew(s3));
// 	node1 = head;
// 	while (node1)
// 	{
// 		if (i == 1)
// 			ft_lstdelone(node1, d);
// 		printf("|OLD| %s\n", node1->content);
// 		node1 = node1->next;
// 		i++;
// 	}
// 	node2 = ft_lstmap(head,test,d);
// 	while (node2)
// 	{
// 		printf("|NEW| %s\n", node2 -> content);
// 		node2 = node2 -> next;
// 	}
// 	}

// int main()
// {
// 	t_list	*root;
// 	root = ft_lstnew("hi");
// 	t_list	*root2;
// 	root2 = ft_lstnew("hi2");
// 	t_list	*root3;
// 	root3 = ft_lstnew("hi3");
// 	root->next=root2;
// 	root2->next=root3;
// 	root3->next=NULL;
// 	printf("%s",root2->content);
// 	return 0;
// }
// int main()
// {
// 	t_list *root;
// 	t_list *root2;
// 	t_list *root3;
// 	int	i = 0;
// 	char s1[] = "a";
// 	char s2[] = "b";
// 	char s3[] = "c";
// 	root = NULL;

// 	ft_lstadd_back(&root,ft_lstnew(s1));
// 	ft_lstadd_back(&root,ft_lstnew(s2));
// 	ft_lstadd_back(&root,ft_lstnew(s3));
// 	root2 = root;
// 	while (root2)
// 	{
// 		if (i == 0)
// 			ft_lstdelone(root2,d);
// 		printf("ADD BACK %s\n",root2 -> content);
// 		root2 = root2 -> next;
// 		i++;
// 	}
// 	root3 = ft_lstmap(root,test,d);
// 	while (root3)
// 	{
// 		printf("MAPI %s\n",root3 -> content);
// 		root3 = root3 -> next;
// 		i++;
// 	}
// 	return 0;
// }
