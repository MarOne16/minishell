/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:33:25 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/15 23:01:50 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '_')
			i++;
		else
		{
			printf(" '%s' not valid\n", s);
			g_lob->exit_status = 2;
			return (0);
		}
		while (ft_isalnum(s[i]) || s[i] == '_')
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

void	free_var_exp(char *s, int size)
{
	t_my_list	*temp_env;
	t_my_list	*tmp;
	int			i;

	i = 0;
	temp_env = (g_lob->exp);
	while (temp_env && temp_env->next)
	{
		if (!ft_strncmp(s, temp_env->name, size) \
		&& (int)ft_strlen(temp_env->name) == size && i++ == 0)
		{
			tmp = temp_env;
			temp_env = tmp->next;
			g_lob->exp = temp_env;
		}
		else if (!ft_strncmp(s, temp_env->next->name, size) \
		&& (int)ft_strlen(temp_env->next->name) == size)
		{
			tmp = temp_env->next;
			temp_env->next = tmp->next;
			free(tmp);
		}
		temp_env = temp_env->next;
	}
	free_var_env(s, size);
}

void	free_var_env(char *s, int size)
{
	t_my_list	*temp_env;
	t_my_list	*tmp;
	int			i;

	i = 0;
	temp_env = (g_lob->env);
	while (temp_env && temp_env->next)
	{
		if (!ft_strncmp(s, temp_env->name, size) \
		&& (int)ft_strlen(temp_env->name) == size && i++ == 0)
		{
			tmp = temp_env;
			temp_env = tmp->next;
			g_lob->env = temp_env;
		}
		else if (!ft_strncmp(s, temp_env->next->name, size) \
		&& (int)ft_strlen(temp_env->next->name) == size)
		{
			tmp = temp_env->next;
			temp_env->next = tmp->next;
			free(tmp);
		}
		temp_env = temp_env->next;
	}
}

void	ft_unset(char **cmd)
{
	int		size;
	int		i;

	size = size_cmd(cmd);
	if (size == 1)
		return ;
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
	g_lob->environ = list_to_array(g_lob->env);
}
