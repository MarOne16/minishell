/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:03:29 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/09 22:31:22 by mbousouf         ###   ########.fr       */
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
		home = ft_getcwd();
	}
	if (chdir(home) == -1)
	{
		printf("Can't Find home path : %s\n", strerror(errno));
		g_lob->exit_status = 0;
		return ;
	}
	change_env(home, "PWD");
	change_env(old_path, "OLDPWD");
}

void	zig_zag(char *old_path)
{
	char	*home;

	if (my_getenv("OLDPWD"))
	{
		home = my_getenv("OLDPWD");
		printf("%s\n", home);
	}
	else
	{
		home = ft_getcwd();
		printf("%s\n", home);
	}
	if (chdir(home) == -1)
	{
		printf("Can't Find home path : %s\n", strerror(errno));
		g_lob->exit_status = 0;
		return ;
	}
	change_env(home, "PWD");
	change_env(old_path, "OLDPWD");
	change_env("PWD", "OLDPWD");
	change_env("OLDPWD", "OLDPWD");
}

void	get_dir(char *home , char *old_path)
{
	if (chdir(home) == -1)
	{
		perror("Minishell");
		g_lob->exit_status = 1;
		return ;
	}
	home = ft_getcwd();
	change_env(home, "PWD");
	change_env(old_path, "OLDPWD");
}

void	ft_chdir(char **cmd)
{
	int		size;
	char	*old_path;

	size = size_cmd(cmd);
	if (size == 1)
		chdir_home();
	else if (size >= 2)
	{
		old_path = ft_getcwd();
		if (!ft_strncmp(cmd[1], "~", 1) && ft_strlen(cmd[1]) == 1)
			chdir_home();
		else if (!ft_strncmp(cmd[1], "-", 1) && ft_strlen(cmd[1]) == 1)
			zig_zag(old_path);
		else if (old_path == NULL &&( (!ft_strncmp(cmd[1], ".", 1)  \
		&& ft_strlen(cmd[1]) == 1)  || (!ft_strncmp(cmd[1], "..", 2)  \
		&& ft_strlen(cmd[1]) == 2)))
		{
			ft_putstr_fd("No such file or directory\n", 2);
			g_lob->exit_status = 1;
			return ;
		}
		else
			get_dir(cmd[1], old_path);
	}
}
