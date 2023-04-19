/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:33:25 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/18 02:04:01 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_unset_var(char *s)
{
    int i = 0;
    while(s[i])
    {
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
            i++;
        else
        {
            printf(" '%s' not valid\n",s);
            return(0);
        }
        while(((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') 
        || (s[i] >= '0' && s[i] <= '9') ||s[i] == '_')) 
            i++;
        if(s[i] != '\0')
        {
            printf(" '%s' not valid\n",s);
            return(0);
        }
    }
    return(1);
}

void free_var_exp(char *s , int size)
{
    t_list* temp_env = *(glob->exp); 
    while(temp_env && temp_env->next)
    {
        if(!ft_strncmp(s,temp_env->next->name,size) && (int)ft_strlen(temp_env->next->name) == size)
        {
            free(temp_env->next);
            temp_env->next = NULL;
            free_var_env(s,size);
        }
        temp_env = temp_env->next;
    }
    return;
}
void free_var_env(char *s , int size)
{
    t_list* temp_env = *(glob->env); 
    while(temp_env && temp_env->next)
    {
        if(!ft_strncmp(s,temp_env->next->name,size) && (int)ft_strlen(temp_env->next->name) == size)
        {
            free(temp_env->next);
            temp_env->next = NULL;
        }
        temp_env = temp_env->next;
    }
    return;
}

void ft_unset(t_cmd *cmd)
{
    t_cmd *tmp;
    int size = size_cmd(cmd);
    if(size == 1)
    {
        return;
    }
    else if(size == 2)
    {
        if(check_unset_var(cmd->next->cmd))
            free_var_exp(cmd->next->cmd,ft_strlen(cmd->next->cmd));
    }
    else if(size >2)
    {
        tmp = cmd->next;
        while(tmp && tmp->next)
        {
            if(check_unset_var(tmp->cmd))
                free_var_exp(tmp->cmd,ft_strlen(tmp->cmd));
            tmp = tmp->next;
        }
    }
}