/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 02:37:20 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/09 19:24:53 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	frepath(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		free(cmd[j]);
		j++;
	}
	free(cmd);
}

char	*f_slach(char *ar)
{
	char	**tab;
	char	*str;

	tab = ft_my_split(ar, ' ', 0);
	str = ft_strjoin("/", tab[0]);
	frepath(tab);
	return (str);
}

char	*pathcmd(char *str)
{
	int		i;
	char	**path;
	char	*s;
	char	*t;

	i = 0;
	if (g_lob->environ && getenv("PATH") != NULL)
	{
		path = ft_my_split(getenv("PATH"), ':', 0);
		while (path[i])
		{
			t = f_slach(str);
			s = ft_strjoin(path[i], t);
			if (!access(s, X_OK))
			{
				frepath(path);
				return (s);
			}
			i++;
		}
		frepath(path);
	}
	ft_putstr_fd("path not set \n", 2);
	return (NULL);
}

int	file_info(int fd, char *s)
{
	struct stat	file_stats;

	if (lstat(s, &file_stats) == 0)
	{
		if (S_ISREG(file_stats.st_mode))
			return (ft_putstr_fd("Permission denied.\n", fd), 126);
		else if (S_ISDIR(file_stats.st_mode))
			return (ft_putstr_fd("is a directory.\n", fd), 126);
		else if (S_ISCHR(file_stats.st_mode))
			return (ft_putstr_fd("is a character device.\n", fd), 127);
		else if (S_ISBLK(file_stats.st_mode))
			return (ft_putstr_fd("is a block device.\n", fd), 127);
		else if (S_ISFIFO(file_stats.st_mode))
			return (ft_putstr_fd("is a FIFO/pipe.\n", fd), 125);
		else if (S_ISSOCK(file_stats.st_mode))
			return (ft_putstr_fd("is a socket.\n", fd), 125);
		else if (S_ISLNK(file_stats.st_mode))
			return (ft_putstr_fd("is a symbolic link.\n", fd), 126);
		else
			return (ft_putstr_fd("type is unknown.\n", fd), 127);
	}
	else
		return (ft_putstr_fd("No such file or directory.\n", fd), 127);
}

void	ex_cmd(char **cmd)
{
	char	*exe;
	pid_t	pid;
	int		status;
	int		ex;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(cmd[0], '/'))
		{
			if (execve(cmd[0], cmd, g_lob->environ) == -1)
			{
				ex = file_info(2, cmd[0]);
				exit(ex);
			}
		}
		exe = pathcmd(cmd[0]);
		if (execve(exe, cmd, g_lob->environ) == -1)
		{
			perror("error");
			ft_putstr_fd("command not found.\n", 2);
			exit(127);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				g_lob->exit_status = WEXITSTATUS(status);
	}
}

void	mex_cmd(char **cmd)
{
	char	*exe;
	int		ex;

	if (ft_strchr(cmd[0], '/'))
	{
		if (execve(cmd[0], cmd, g_lob->environ) == -1)
		{
			ex = file_info(2, cmd[0]);
			exit(ex);
		}
	}
	exe = pathcmd(cmd[0]);
	if (execve(exe, cmd, g_lob->environ) == -1)
	{
		perror("error");
		ft_putstr_fd("Minishell: multi_command not found\n", 2);
		exit(127);
	}
}
