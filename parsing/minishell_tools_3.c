/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:48:57 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/14 15:52:44 by mqaos            ###   ########.fr       */
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
				tmp->lakher = cmd;
				close_all(tmp->fd);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
