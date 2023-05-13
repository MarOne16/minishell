/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newRealease.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:47:17 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/12 23:02:10 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		tmp = ft_my_split(env[i], '=', 1);
		if (tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&listenv, ft_my_lstnew(tmp[0], \
			ft_strjoin_mini("=", tmp[1])));
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
	i = 0;
	while (s_env[i])
	{
		tmp = ft_my_split(s_env[i], '=', 1);
		if (tmp && (*tmp) && tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&list, \
			ft_my_lstnew(tmp[0], ft_strjoin_mini("=", tmp[1])));
		}
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
