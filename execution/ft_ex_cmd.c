/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 02:37:20 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/05 14:24:00 by mbousouf         ###   ########.fr       */
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

	tab = ft_my_split(ar, ' ');
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
	(void) str;
	i = 0;
	if (glob->env)
	{
		path = ft_my_split(find_var_exp("PATH",ft_strlen("PATH"))->value+1, ':');
		while (path[i])
		{
			t = f_slach(str);
			s = ft_strjoin(path[i], t);
			if (!access(s, X_OK))
			{
				frepath(path);
				return (free (t), s);
			}
			i++;
			free(s);
			free(t);
		}
		frepath(path);
	}
	return (NULL);
}

int file_info(int fd ,char *s)
{
	struct stat file_stats;
	int ex = 0;

    if (lstat(s, &file_stats) == 0) 
	{
        if (S_ISREG(file_stats.st_mode)) 
		{
            ft_putstr_fd("Permission denied.\n",fd);
			ex = 126;
        } else if (S_ISDIR(file_stats.st_mode)) {
            ft_putstr_fd("is a directory.\n",fd);
			ex = 126;
        } else if (S_ISCHR(file_stats.st_mode)) {
            ft_putstr_fd("is a character device.\n",fd);
			ex = 127;
        } else if (S_ISBLK(file_stats.st_mode)) {
            ft_putstr_fd("is a block device.\n",fd);
			ex = 127;
        } else if (S_ISFIFO(file_stats.st_mode)) {
            ft_putstr_fd("is a FIFO/pipe.\n",fd);
			ex = 125;
        } else if (S_ISSOCK(file_stats.st_mode)) {
            ft_putstr_fd("is a socket.\n",fd);
			ex = 125;
        } else if (S_ISLNK(file_stats.st_mode)) {
            ft_putstr_fd("is a symbolic link.\n",fd);
			ex = 126;
        } else {
            ft_putstr_fd("type is unknown.\n",fd);
			ex = 127;
        }
    } 
	else 
	{
        perror("Minishell");
		ex = 127;
    }
	return(ex);
}


void ex_cmd(char ** cmd)
{
	char *exe;
	extern char ** environ;
	pid_t pid;
	int status;
	int ex;
	

	pid = fork();
		if(pid == 0)
		{
			if(ft_strchr(cmd[0],'/'))
			{
					if(execve(cmd[0], cmd, environ) == -1)
					{
						ex = file_info(2,cmd[0]);
						exit(ex);
					}
			}
			exe = pathcmd(cmd[0]);
			{
				if(execve(exe,cmd,environ) == -1)
				{
						ft_putstr_fd("Minishell: command not found\n",2);
						exit(127);
				}
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) != 0)
						glob->exit_status = WEXITSTATUS(status);
			}
			else {
					fprintf(stderr, "Command terminated abnormally\n");
			}
		}
}
void mex_cmd(char ** cmd)
{
	char *exe;
	int ex;
	extern char ** environ;
	if(ft_strchr(cmd[0],'/'))
	{
		if(execve(cmd[0], cmd, environ) == -1)
		{
			ex = file_info(2,cmd[0]);
			exit(ex);
		}
	}
	exe = pathcmd(cmd[0]);
	if(execve(exe, cmd, environ) == -1)
	{
		ft_putstr_fd("Minishell: command not found\n",2);
		exit(127);
	}
}