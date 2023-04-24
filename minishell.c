/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 16:16:25 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *input = NULL;
	char *newinput = NULL;
	t_exe       *all = NULL;

	while ((input = ft_readline()))
	{	
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!ft_strcmp(input, "exit"))
			break;
		newinput = replace_vars(input);
		feedlist(&all, newinput);
		while (all)
		{
			int i = 0;
			while (all->lakher[i])
			{
				printf(AC_BLUE"%s \t",(char *)all->lakher[i]);
				i++;
			}
			while (all->fd)
			{
				printf(AC_BLUE"%d \t", all->fd->fd);
				all->fd = all->fd->next;
			}
			puts("");
			all = all->next;
		}
		all = NULL;
		// // forcfree(&all);
	}
	exit(0);
	return 0;
}