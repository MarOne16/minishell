/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newRealease.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:47:17 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/08 12:25:09 by mbousouf         ###   ########.fr       */
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
		tmp = ft_my_split(env[i], '=', 1);
		if (tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&listenv, ft_my_lstnew(tmp[0], \
			ft_strjoin("=", tmp[1])));
			free(tmp[1]);
		}
		free(tmp);
		i++;
	}
	g_lob->env = listenv;
}

char **sort_env(char **env)
{
	char	**list;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	list = env;
	while (list[i])
	{
		j = i + 1;
		while (list[j])
		{
			if (list[j][k] == list[i][k])
			{
				k++;
			}
			else if (list[j][k] < list[i][k])
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			else
			{
				k = 0;
				j++;
			}
		}
		i++;
	}
	return (list);
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
		tmp = ft_my_split(s_env[i], '=' , 1);
		if (tmp && (*tmp) && tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&list, \
			ft_my_lstnew(tmp[0], ft_strjoin("=", tmp[1])));
			free(tmp[1]);
		}
		i++;
		free(tmp);
	}
	(g_lob->exp) = list;
}

int	size_fd(t_fd *fd)
{
	int	i;

	i = 0;
	while (fd)
	{
		i++;
		fd = fd->next;
	}
	return (i);
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

int out_fd(t_fd *tabfd)
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

void o_cmd(t_exe *all)
{
	int	saved_stdin_fd;
	int	saved_stdout_fd;
	int	infd;
	int	outfd;	
	saved_stdin_fd = dup(STDIN_FILENO);
	saved_stdout_fd = dup(STDOUT_FILENO);
	infd = in_fd(all->fd);
	outfd = out_fd(all->fd);
	if (infd)
		dup2(infd, STDIN_FILENO);
	if (outfd)
		dup2(outfd, STDOUT_FILENO);
	check_builtin(all);
	if (infd)
		dup2(saved_stdin_fd, STDIN_FILENO);
	if (outfd)
		dup2(saved_stdout_fd, STDOUT_FILENO);
}

void m_cmd(t_exe *all)
{
	int	saved_stdin_fd;
	int	saved_stdout_fd;
	int	infd;	
	int	outfd;

	saved_stdin_fd = dup(STDIN_FILENO);
	saved_stdout_fd = dup(STDOUT_FILENO);
	infd = in_fd(all->fd);
	outfd = out_fd(all->fd);
	if (infd)
		dup2(infd, STDIN_FILENO);
	if (outfd)
		dup2(outfd, STDOUT_FILENO);
	check_builtin_multi(all);
	if (infd)
	{
		close(infd);
		dup2(saved_stdin_fd, STDIN_FILENO);
	}
	if (outfd)
	{
		close(outfd);
		dup2(saved_stdout_fd, STDIN_FILENO);
	}
}

void wait_childs(int size, int *child_pids)
{
	int	j;
	int	status;

	j = 0;

	while (j < size)
	{
		if (waitpid(child_pids[j], &status, 0) == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				g_lob->exit_status = WEXITSTATUS(status);
		}
		j++;
	}
}

void lot_cmd(t_exe *all, int size)
{
	int		fd[2];
	int		pid;
	int		saved_in_fd;
	pid_t	child_pids[size];
	int		i;

	i = 0;
	saved_in_fd = 0;
	while (all)
	{
		ft_pipe(fd);
		pid = ft_fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(saved_in_fd, STDIN_FILENO);
			if (i < size - 1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			m_cmd(all);
		}
		else
		{
			if (i == size - 1)
				close(saved_in_fd);
			close(fd[1]);
			saved_in_fd = fd[0];
			child_pids[i++] = pid;
		}
		all = all->next;
	}
	wait_childs(size, child_pids);
}

void session(t_exe *all)
{
	int	size;

	size = size_prc(all);
	if (size == 1)
	{
		o_cmd(all);
	}
	if (size > 1)
	{
		lot_cmd(all, size);
	}
}
