/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:03:29 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/17 05:18:24 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char * get_home(void)
{
    t_list* temp_env;
    
    temp_env = NULL;

    temp_env = *(glob->env);
        if(!temp_env)
            return(0);
    while(temp_env)
    {
        if(!ft_strncmp("HOME",temp_env->name,4) && ft_strlen(temp_env->name) == 4) 
        {
            return(temp_env->value);
        }
        temp_env = temp_env->next;
    }
    return(0);
}
t_list *find_var_env(char *s , int size)
{
    t_list* temp_env = *(glob->env);
    while(temp_env)
    {
        if(!ft_strncmp(s,temp_env->name,size) && (int)ft_strlen(temp_env->name) == size)
        {
            return(temp_env);
        }
        temp_env = temp_env->next;
    }
    return(0);
}

t_list *find_var_exp(char *s , int size)
{
    t_list* temp_env = *(glob->exp); 
    while(temp_env)
    {
        if(!ft_strncmp(s,temp_env->name,size) && (int)ft_strlen(temp_env->name) == size)
        {
            return(temp_env);
        }
        temp_env = temp_env->next;
    }
    return(0);
}

void change_env(char *s,char *modified)
{
    t_list *change;
    change = find_var_env(modified,ft_strlen(modified));
    change->value = s;
    change = NULL;
    change = find_var_exp(modified,ft_strlen(modified));
    change->value = s;
}
void chdir_home (void)
{
    char * old_path;
    char *home;
    home = NULL;

    old_path = getcwd(NULL,0);
    home = get_home();
        if(chdir(home) == -1)
        {
                printf("Can't Find home path : %s\n",strerror(errno));
                return;
        }
    change_env(home,"PWD=");
    change_env(old_path,"OLDPWD=");
}
void ft_chdir(t_cmd *cmd)
{
    int size;
    char * old_path;
    char *home;
    home = NULL;
    size = size_cmd(cmd);
    if(size == 1)
    {
        chdir_home();
    }
    if(size >= 2)
    {

        old_path = getcwd(NULL,0);
        if(!ft_strncmp(cmd->next->cmd,"~",1) && ft_strlen(cmd->next->cmd) == 1)
        {
            chdir_home();
            return;
        }
        else if(!ft_strncmp(cmd->next->cmd,"-",1) && ft_strlen(cmd->next->cmd) == 1)
        {
            home = find_var_env("OLDPWD",ft_strlen("OLDPWD"))->value;
            if(chdir(home) == -1)
            {
                printf("%s\n",strerror(errno));
                return;
            }
            printf("%s\n",home);
            home = getcwd(NULL,0);
                change_env(home,"PWD");
                change_env(old_path,"OLDPWD");
            return;
        }
        else if (old_path == NULL && !ft_strncmp(cmd->next->cmd,".",1) && ft_strlen(cmd->next->cmd) == 1)
        {
           printf("%s\n",cmd->next->cmd);
           return;
        }
            home = cmd->next->cmd;
            if(chdir(home) == -1)
            {
                printf("%s\n",strerror(errno));
                return;
            }
            home = getcwd(NULL,0);
            change_env(home,"PWD");
            change_env(old_path,"OLDPWD");
    }
}