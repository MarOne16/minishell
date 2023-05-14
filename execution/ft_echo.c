/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:47:41 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/03 11:23:37 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[0] == '-')
		{
			i++;
			while (s[i] == 'n')
				i++;
			if (s[i] != '\0')
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

void	print_cmd(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int	size_cmd(char **cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp[i])
	{
		i++;
	}
	return (i);
}

void	ft_echo(char **cmd)
{
	int	size;
	int	i;

	size = size_cmd(cmd);
	i = 0;
	if (size == 1)
		printf("\n");
	else if (size == 2)
	{
		if (check_n(cmd[1]))
			return ;
		else
			printf("%s\n", cmd[1]);
	}
	else if (size > 2)
	{
		multi_echo(&cmd[1]);
	}
}

void	multi_echo(char **cmd)
{
	int	i;

	if (check_n(*cmd))
	{
		i = 1;
		while (cmd[i])
		{
			if (!check_n(cmd[i]))
				break ;
			i++;
		}
		cmd = &cmd[i];
		print_cmd(cmd);
	}
	else
	{
		print_cmd(cmd);
		printf("\n");
	}
}
