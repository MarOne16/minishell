/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:57:56 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/09 05:41:53 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_exp()
{
    t_list *list;
    if(*glob->exp)
    {
        list = (*glob->exp);
        while(list)
        {
            printf("declare -x %s=%s\n",list->name,list->value);
            list = list->next;
        }
    }
}

void ft_exp(t_cmd *cmd)
{
    int size;
    size = size_cmd(cmd);

    if(size == 1)
    {
        print_exp();
    }
}