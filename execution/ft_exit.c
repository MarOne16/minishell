/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:31:11 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/03 16:18:25 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' || s[i] == '-')
			i++;
		if (ft_isdigit(s[i]) == 0)
		{
			ft_putstr_fd(s, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
}

void	multi_cmd(char *cmd)
{
	check_num(cmd);
	ft_putstr_fd(" too many arguments\n", 2);
	g_lob->exit_status = 1;
}

void	ft_exit(char **cmd)
{
	int			i;
	int			estatus;

	i = 0;
	if (size_cmd(cmd) == 1)
	{
		ft_putchar_fd('\n', 2);
		exit(0);
	}
	else if (size_cmd(cmd) == 2)
	{
		check_num(cmd[1]);
		estatus = ft_atoi(cmd[1]);
		if (estatus < 0)
			estatus = 256 + estatus;
		else if (estatus > 255)
			estatus = estatus % 256;
		ft_putchar_fd('\n', 2);
		exit((int)estatus);
	}
	else if (size_cmd(cmd) > 2)
		multi_cmd(cmd[1]);
}
