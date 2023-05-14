/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:56:51 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/14 20:10:57 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_orgin(void)
{
	t_my_list	*list;

	list = (g_lob->env);
	while (list)
	{
		if (!ft_strncmp(list->name, "PWD", 4))
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
		s = ft_getcwd();
		if (s == NULL)
		{
			s = get_orgin();
			if (s == NULL)
				s = g_lob->pwd;
		}
		if (s == NULL)
		{
			printf("PWD not set");
		}
		printf("%s\n", s);
	}
}

char	*ft_getcwd(void)
{
	char	*cwd;
	char	*cwd_2;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_lob->exit_status = 1;
		return (NULL);
	}
	cwd_2 = ft_strdup_mini(cwd, 0);
	free(cwd);
	return (cwd_2);
}

int	out_fd(t_fd *tabfd)
{
	int	i;

	i = 0;
	while (tabfd)
	{
		if (tabfd->type == 'a' || tabfd->type == 'o')
			i = tabfd->fd;
		tabfd = tabfd->next;
	}
	return (i);
}
