/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Realeasebeta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:22:42 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/14 17:57:21 by mqaos            ###   ########.fr       */
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

void	run_command(t_exe *all, t_lot *l, int size)
{
	while (all)
	{
		if (all->lakher && all->lakher[0] && \
		all->lakher[0][0] == 0 && all->next)
			all = all->next;
		l->pid = ft_fork();
		if (l->pid == 0)
		{
			if (all->next)
				dup2(l->fd[l->j + 1], STDOUT_FILENO);
			if (l->j != 0)
				dup2(l->fd[l->j - 2], STDIN_FILENO);
			l->i = 0;
			while (l->i < size * 2)
				close(l->fd[l->i++]);
			m_cmd(all);
		}
		else
			l->child_pids[l->k++] = l->pid;
		all = all->next;
		l->j = l->j + 2;
	}
}

void	lot_cmd(t_exe *all, int size)
{
	t_lot	l;

	l.i = 0;
	l.j = 0;
	l.k = 0;
	l.child_pids = ft_malloc(sizeof(pid_t) * size, 0);
	l.fd = ft_malloc(sizeof(int) * (size * 2), 0);
	while (l.i < size)
		ft_pipe(&l.fd[l.i++ *2]);
	run_command(all, &l, size);
	l.i = 0;
	while (l.i < size * 2)
		close(l.fd[l.i++]);
	l.i = 0;
	wait_childs(l.k, l.child_pids);
}
