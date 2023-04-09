/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:56:51 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/09 02:45:06 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *get_orgin(void)
{
    t_list *list;
    list = (*glob->env);
    while(list)
    {
        if(!ft_strncmp(list->name,"PWD",3) && ft_strlen(list->name) == 3)
        {
            return(list->value);
        }
        // printf("%s=%s\n",list->name,list->value);
        list = list->next;
    }
    return(NULL);
}
void ft_pwd(t_cmd *pwd)
{
    char *s;
    if(pwd->cmd)
    {
        s = getcwd(NULL,0);
        if(s == NULL)
        {
            s = get_orgin();
        }       
        printf("%s\n",s);
    }
}