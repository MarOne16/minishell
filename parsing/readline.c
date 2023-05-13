/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/13 22:39:06 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(char *line)
{
	char	*tmp;
	char	*line_copy;

	tmp = NULL;
	line_copy = NULL;
	rl_free_line_state();
	line_copy = strdup(line);
	tmp = readline(line_copy);
	if (line_copy != NULL)
	{
		add_history(line_copy);
		free(line_copy);
	}
	return (tmp);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			g_lob->exit_status = 130;
			printf("\n");
		}
		else
		{
			g_lob->exit_status = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signum == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			printf("Quit: 3\n");
		else
			signal(SIGQUIT, SIG_IGN);
	}
}

void	sig_here(int sig)
{
	(void)sig;
	g_lob->rd = 1;
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
