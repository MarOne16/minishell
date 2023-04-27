/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/27 17:00:38 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// free t_list *g_all
void	free_all(void)
{
	t_list	*tmp;

	while (g_all)
	{
		tmp = g_all;
		g_all = g_all->next;
		free(tmp->content);
		free(tmp);
	}
	g_all = NULL;
}

int	main(void)
{
	char	*input;
	char	*newinput;
	t_exe	*all;
	int		i;

	input = NULL;
	all = NULL;
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		rl_catch_signals = 0;
		input = ft_readline();
		if (!input)
			break ;
		if (!ft_strcmp(input, "exit"))
			break ;
		newinput = replace_vars(input);
		feedlist(&all, newinput);
		while (all)
		{
			i = -1;
			while (all->lakher[++i])
				printf("lakher[%d] = %s\n", i, (char *)all->lakher[i]);
			while (all->fd)
			{
				printf("fd = %d\n", all->fd->fd);
				all->fd = all->fd->next;
			}
			all = all->next;
		}
		all = NULL;
		free(input);
	}
	free_all();
	exit(0);
	return (0);
}