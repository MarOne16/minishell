/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 02:37:20 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/24 17:29:04 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ex_cmd(char ** cmd)
{
	char *exe;
	pid_t pid;
	exe = pathcmd(cmd[0]);
	if(!exe)
	{
		printf(" '%s' command not found \n",cmd[0]);
	}
	else
	{
		pid = fork();
		if(pid == 0)
			execve(exe,cmd,NULL);
		else
			wait(0);
	}
}