/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 02:37:20 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/13 14:34:41 by mqaos            ###   ########.fr       */
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
	str = ft_strjoin_mini("/", tab[0]);
	return (str);
}

char	*pathcmd(char *str)
{
	int		i;
	char	**path;
	char	*s;
	char	*t;

	i = 0;
	if (g_lob->environ && my_getenv("PATH") != NULL)
	{
		path = ft_my_split(my_getenv("PATH"), ':', 0);
		while (path[i])
		{
			t = f_slach(str);
			s = ft_strjoin_mini(path[i], t);
			if (!access(s, X_OK))
			{
				frepath(path);
				return (s);
			}
			i++;
		}
	}
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
