/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:48:57 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/16 16:53:01 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all(t_fd *fd)
{
	t_fd	*tmp;

	while (fd)
	{
		tmp = fd;
		fd = fd->next;
		close(tmp->fd);
	}
}

void	next_cmd(t_exe **all)
{
	t_exe	*tmp;
	t_fd	*tmp2;
	char	**cmd;

	tmp = *all;
	cmd = ft_malloc((sizeof(char *) + 1), 1);
	while (tmp)
	{
		tmp2 = tmp->fd;
		while (tmp2)
		{
			if (tmp2->fd == -1)
			{
				cmd[0] = ft_strdup_mini("", 1);
				tmp->last = cmd;
				close_all(tmp->fd);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	pip_count(char *str)
{
	int	*hash;
	int	i;
	int	count;

	i = 0;
	feedhashtable(&hash, str);
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && hash[i] == 0)
			count++;
		i++;
	}
	return (count);
}

void	sig_handler_2(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_lob->exit_status = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_lob->exit_status = 130;
	}
}
