/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Realeasebeta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:22:42 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/10 16:28:48 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	o_cmd(t_exe *all)
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

void	m_cmd(t_exe *all)
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

void	wait_childs(int size, int *child_pids)
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
				g_lob->exit_status = WEXITSTATUS(status);
		j++;
	}
}

void	lot_cmd(t_exe *all, int size)
{
	int		*fd;
	int		pid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fd = ft_malloc(sizeof(int) * (size * 2), 0);
	while(i < size)
		ft_pipe(&fd[i++ * 2]);
	while (all)
	{
		pid = ft_fork();
		if (pid == 0)
		{
			if (all->next)
				dup2(fd[j + 1], STDOUT_FILENO);
			if (j != 0)
				dup2(fd[j - 2],STDIN_FILENO);
			i = 0;
			while(i < size * 2)
				close(fd[i++]);
			m_cmd(all);
		}
		all = all->next;
		j = j + 2;
	}
		i = 0;
		while(i < size * 2)
			close(fd[i++]);
		i = 0;
		while(i < size)
		{
			wait(NULL);
			i++;
		}
}

void	session(t_exe *all)
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
