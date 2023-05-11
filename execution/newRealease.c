/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newRealease.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:47:17 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/10 16:27:21 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void	creat_env(char **env)
{
	int			i;
	char		**tmp;
	t_my_list	*listenv;

	i = 0;
	listenv = NULL;
	while (env[i] != NULL)
	{
		i++;
	}
	i = 0;
	while (env[i])
	{
		tmp = ft_my_split(env[i], '=');
		if (tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&listenv, ft_my_lstnew(tmp[0], \
			ft_strjoin("=", tmp[1])));
		}
		i++;
	}
	g_lob->env = listenv;
}

void	creat_exp(char **env)
{
	char		**s_env;
	char		**tmp;
	t_my_list	*list;
	int			i;

	s_env = NULL;
	list = NULL;
	i = 0;
	s_env = sort_env(env);
	while (s_env[i])
		i++;
	i = 0;
	while (s_env[i])
	{
		tmp = ft_my_split(s_env[i], '=');
		if (tmp && (*tmp) && tmp[0] && tmp[1])
			ft_my_lstadd_back(&list, \
			ft_my_lstnew(tmp[0], ft_strjoin("=", tmp[1])));
		i++;
	}
	(g_lob->exp) = list;
}

int	in_fd(t_fd *tabfd)
{
	int	i;

	i = 0;
	while (tabfd)
	{
		if (tabfd->type == 'i' || tabfd->type == 'h')
			i = tabfd->fd;
		tabfd = tabfd->next;
	}
	return (i);
}

int	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("Cant' Not creat pipe ");
		exit(errno);
	}
	else
		return (0);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Cant ' Not creat fork");
		exit(errno);
	}
	else
		return (pid);
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
