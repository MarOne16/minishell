/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:47:41 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/04 17:48:26 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_n(char *s)
{
    int i = 0;
    if(!s)
        return(0);
    while(s[i])
    {
        if(s[0] == '-')
        {
            i++;
            while(s[i] == 'n')
                i++;
            if(s[i] != '\0')
                return(0);
                
        }
        else
            return(0);
    }
    return(1);
}

void print_cmd(t_cmd *cmd)
{
    while(cmd)
    {
        printf("%s",cmd->cmd);
        if(cmd->next)
        printf(" ");
        cmd = cmd->next;
    }
}

int size_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	int i;

	i = 0;
	tmp = cmd;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void ft_echo(t_cmd *cmd)
{
    int size = size_cmd(cmd);
    if(size == 1)
        printf("\n");
    else if (size == 2)
    {
        if(check_n(cmd->next->cmd))
            return;
        else
            printf("%s\n",cmd->next->cmd);
    }
    else if(size > 2)
    {
        cmd = cmd->next;
        if(check_n(cmd->cmd))
        {
            while (cmd)
            {
                if(!check_n(cmd->cmd))
                    break;
                cmd = cmd->next;
            }
            print_cmd(cmd);
        }
        else
        {
            print_cmd(cmd);
            printf("\n");
        }
    }
}