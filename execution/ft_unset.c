/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:33:25 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/02 15:41:47 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_unset_var(char *s)
{
	int i = 0;
	while (s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
			i++;
		else
		{
			printf(" '%s' not valid\n", s);
			g_lob->exit_status = 2;
			return (0);
		}
		while (((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			i++;
		if (s[i] != '\0')
		{
			printf(" '%s' not valid\n", s);
			g_lob->exit_status = 2;
			return (0);
		}
	}
	return (1);
}

void free_var_exp(char *s, int size)
{
	t_my_list *temp_env = (g_lob->exp);
	t_my_list *tmp;
	while (temp_env && temp_env->next)
	{
		if (!ft_strncmp(s, temp_env->next->name, size) && (int)ft_strlen(temp_env->next->name) == size)
		{
			tmp = temp_env->next;
			temp_env->next = tmp->next;
			free(tmp);
			free_var_env(s, size);
		}
		temp_env = temp_env->next;
	}
	return;
}
void free_var_env(char *s, int size)
{
	t_my_list *temp_env = (g_lob->env);
	t_my_list *tmp;
	while (temp_env && temp_env->next)
	{
		if (!ft_strncmp(s, temp_env->next->name, size) && (int)ft_strlen(temp_env->next->name) == size)
		{
			tmp = temp_env->next;
			temp_env->next = tmp->next;
			free(tmp);
		}
		temp_env = temp_env->next;
	}
	return;
}

void ft_unset(char **cmd)
{
	int size = size_cmd(cmd);
	int i;
	if (size == 1)
	{
		return;
	}
	else if (size == 2)
	{
		if (check_unset_var(cmd[1]))
			free_var_exp(cmd[1], ft_strlen(cmd[1]));
	}
	else if (size > 2)
	{
		cmd = &cmd[1];
		i = 0;
		while (cmd[i])
		{
			if (check_unset_var(cmd[i]))
				free_var_exp(cmd[i], ft_strlen(cmd[i]));
			i++;
		}
	}
}