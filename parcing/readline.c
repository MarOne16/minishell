/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/28 10:43:40 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(void)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("Minishell> ");
	if (line)
		add_history(line);
	return (line);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sig_here(int sig)
{
	(void)sig;
	ft_rl_done = 1;
	rl_done = 1;
}

int	my_event(void)
{
	return (0);
}

void	sig_int(void)
{
	rl_event_hook = my_event;
	signal(SIGINT, sig_here);
	signal(SIGQUIT, SIG_IGN);
}