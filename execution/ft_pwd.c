/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:56:51 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/03 16:04:38 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_orgin(void)
{
	t_my_list	*list;

	list = (g_lob->env);
	while (list)
	{
		if (!ft_strncmp(list->name, "PWD", 4) && ft_strlen(list->name) == 4)
		{
			return (list->value);
		}
		list = list->next;
	}
	return (NULL);
}

void	ft_pwd(char **pwd)
{
	char	*s;

	if (pwd[0])
	{
		s = getcwd(NULL, 0);
		if (s == NULL)
		{
			s = get_orgin();
		}
		printf("%s\n", s);
	}
}