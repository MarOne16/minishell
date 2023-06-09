/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/16 16:54:28 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(char *rl_prompt)
{
	char	*line;

	line = NULL;
	if (!isatty(STDIN_FILENO))
	{
		printf("Error: Input is not coming from a minishell.\n");
		return (NULL);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(rl_prompt);
	rl_catch_signals = 0;
	if (line)
		add_history(line);
	return (line);
}

void	sig_handler(int signum)
{
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (signum == SIGINT)
		{
			g_lob->exit_status = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (signum == SIGQUIT)
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
