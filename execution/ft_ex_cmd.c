/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 02:37:20 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/02 15:41:47 by mqaos            ###   ########.fr       */
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
	if (g_lob->env)
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

void file_info(char *s)
{
	struct stat file_stats;

    if (lstat(s, &file_stats) == 0) 
	{
        if (S_ISREG(file_stats.st_mode)) {
            printf("Permission denied.\n");
        } else if (S_ISDIR(file_stats.st_mode)) {
            printf("is a directory.\n");
        } else if (S_ISCHR(file_stats.st_mode)) {
            printf("is a character device.\n");
        } else if (S_ISBLK(file_stats.st_mode)) {
            printf("is a block device.\n");
        } else if (S_ISFIFO(file_stats.st_mode)) {
            printf("is a FIFO/pipe.\n");
        } else if (S_ISSOCK(file_stats.st_mode)) {
            printf("is a socket.\n");
        } else if (S_ISLNK(file_stats.st_mode)) {
            printf("is a symbolic link.\n");
        } else {
            printf("type is unknown.\n");
        }
    } 
	else 
	{
        perror("Minishell");
    }
}


void ex_cmd(char ** cmd)
{
	char *exe;
	extern char ** environ;
	pid_t pid;
	

	pid = fork();
		if(pid == 0)
		{
			exe = pathcmd(cmd[0]);
			if(ft_strchr(cmd[0],'/'))
			{
				if(execve(cmd[0], cmd, environ) == -1)
				{
					file_info(cmd[0]);
					exit(1);
				}
			}
			else if(execve(exe,cmd,environ) == -1)
			{
				ft_putstr_fd("Minishell: one_command not found 1\n",2);
				exit(127);
			}
			
		}
		else
			wait(0);
}
void mex_cmd(char ** cmd)
{
	char *exe;
	extern char ** environ;

	if(ft_strchr(cmd[0],'/'))
	{	
		if(execve(cmd[0], cmd, environ) == -1)
		{
			strerror(errno);
			ft_putstr_fd("Minishell: multi_command not found\n",2);
			exit(127);
		}
	}
	exe = pathcmd(cmd[0]);
	if(execve(exe, cmd, environ) == -1)
	{
		strerror(errno);
		ft_putstr_fd("Minishell: multi_command not found\n",2);
		exit(127);
	}
}