/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:03:29 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/14 18:21:37 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(void)
{
	t_my_list	*temp_env;

	temp_env = (g_lob->env);
	if (!temp_env)
		return (0);
	while (temp_env && temp_env->next)
	{
		if (!ft_strncmp("HOME", temp_env->name, 4) \
		&& ft_strlen(temp_env->name) == 4)
		{
			return (temp_env->value);
		}
		temp_env = temp_env->next;
	}
	return (0);
}

t_my_list	*find_var_env(char *s, int size)
{
	t_my_list	*temp_env;

	temp_env = (g_lob->env);
	while (temp_env)
	{
		if (!ft_strncmp(s, temp_env->name, size) \
		&& (int)ft_strlen(temp_env->name) == size)
		{
			return (temp_env);
		}
		temp_env = temp_env->next;
	}
	return (0);
}

t_my_list	*find_var_exp(char *s, int size)
{
	t_my_list	*temp_env;

	temp_env = (g_lob->exp);
	while (temp_env)
	{
		if (!ft_strncmp(s, temp_env->name, size) \
		&& (int)ft_strlen(temp_env->name) == size)
		{
			return (temp_env);
		}
		temp_env = temp_env->next;
	}
	return (0);
}

void	change_env(char *s, char *modified)
{
	t_my_list	*change;

	change = find_var_env(modified, ft_strlen(modified));
	if (change)
		change->value = s;
	else
		g_lob->exit_status = 0;
	change = NULL;
	change = find_var_exp(modified, ft_strlen(modified));
	if (change)
		change->value = s;
	else
		g_lob->exit_status = 0;
}

void	chdir_home(void)
{
	char	*old_path;
	char	*home;

	old_path = ft_getcwd();
	home = get_home();
	if (home)
		home = ft_substr_mini(home, 1, ft_strlen(home), 0);
	else
	{
		printf("HOME not set\n");
		home = ft_getcwd();
	}
	if (chdir(home) == -1)
	{
		printf("Can't Find home path : %s\n", strerror(errno));
		g_lob->exit_status = 0;
		return ;
	}
	g_lob->pwd = home;
	g_lob->old_pwd = old_path;
	change_env(home, "PWD");
	change_env(old_path, "OLDPWD");
}
