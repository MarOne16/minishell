/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/26 13:58:53 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// garbage collector for the list t_exe t_fd

void	garbage_collector(t_exe **all)
{
	t_exe	*tmp;
	t_exe	*tmp2;
	int		i;

	i = -1;
	tmp = *all;
	while (tmp)
	{
		while (tmp->lakher[++i])
		{
			free(tmp->lakher[i]);
			tmp->lakher[i] = NULL;
		}
		tmp2 = tmp->next;
		free(tmp->lakher);
		while (tmp->fd)
		{
			free(tmp->fd);
			tmp->fd = tmp->fd->next;
		}
		free(tmp);
		tmp = tmp2;
	}
	*all = NULL;
}

int	main()
{
	char	*input;
	char	*newinput;
	t_exe	*all;

	input = NULL;
	all = NULL;
	while (1)
	{
		garbage_collector(&all);
		free(input);
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
	}
	exit(0);
	return (0);
}