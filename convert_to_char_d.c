/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_char_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:40:48 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/19 03:05:36 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sizechar(t_cmd *cmd)
{
	t_cmd	*rest;
	int		i;

	i = 0;
	rest = cmd;
    if (rest && rest->type == 2)
        rest = rest->next;
	while (rest)
	{
		if (rest->type == 2)
			break;
        else if (rest->type == 1)
		    rest = rest->next->next;
        else
        {
		    rest = rest->next;
		    i++;
        }
	}
	return (i);
}
int		size_pip(t_cmd *cmd)
{
	t_cmd	*rest;
	int		i;

	i = 0;
	rest = cmd;
    if (rest && rest->type == 2)
        rest = rest->next;
	while (rest)
	{
        if (rest->type != 2)
        {
            i++;
            while (rest && rest->type != 2)
                rest = rest->next;
        }
        else
		    rest = rest->next;
	}
	return (i);
}

void    table_lakher(t_cmd *cmd, t_exe **lakher)
{
    char **spl;
    t_cmd   *rest;
    int i;

    i = 0;
    rest = cmd;
    spl = malloc((sizechar(rest) + 1) * sizeof(char *));
    if (rest && rest->type == 2)
        rest = rest->next;
    while (rest && rest->type != 2)
    {
        if (rest->next && rest->type == 1)
            rest = rest->next->next;
        else
        {
            spl[i++] = rest->cmd;
            rest = rest->next;
        }
    }
    spl[i] = NULL;
    ft_lstadd_backallcmd(lakher,ft_lstnewallcmd((void *)spl, NULL));
    if (rest && rest->next && rest->next->next)
        table_lakher(rest, lakher);
    
}
