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
		if (s[i] && (s[i] < '0' || s[i] > '9') && s[i] != '-' && s[i] != '+')
		{
			printf("exit\nnumeric argument required\n");
			exit(255);
		}
		i++;
	}
	if (s[i] != '\0')
	{
		printf("exit\nnumeric argument required\n");
		exit(255);
	}
}

void	multi_cmd(char *cmd)
{

	check_num(cmd);
	printf("exit\ntoo many arguments\n");
}

void	ft_exit(char **cmd)
{
	int		size;
	int		i;
	int		estatus;

	size = size_cmd(cmd);
	i = 0;
	if (size == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (size == 2)
	{
		check_num(cmd[1]);
		estatus = ft_atoi(cmd[1]);
		if (estatus < -2147483648 || estatus > 2147483647)
		{
			printf("exit\nnumeric argument required\n");
			exit(255);
		}
		printf("exit\n");
		exit(estatus);
	}
	else if (size > 2)
		multi_cmd(cmd[1]);
}
