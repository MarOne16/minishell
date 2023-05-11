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
		{
			if (WEXITSTATUS(status) != 0)
				g_lob->exit_status = WEXITSTATUS(status);
		}
		j++;
	}
}

void	lot_cmd(t_exe *all, int size)
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
