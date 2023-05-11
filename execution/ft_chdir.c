/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:03:29 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/11 17:00:14 by mbousouf         ###   ########.fr       */
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

	old_path = getcwd(NULL, 0);
	home = get_home();
	if (home)
		home = ft_substr_mini(home, 1, ft_strlen(home), 0);
	else
	{
		home = getcwd(NULL, 0);
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

	if (find_var_env("OLDPWD", ft_strlen("OLDPWD")))
	{
		home = find_var_env("OLDPWD", ft_strlen("OLDPWD"))->value;
		if (home[0] == '=' && home)
			home = ft_substr_mini(home, 1, ft_strlen(home), 0);
	}
	else
	{
		printf("%s\n", " OLDPWD not set");
		g_lob->exit_status = 0;
		return ;
	}
	if (chdir(home) == -1)
	{
		printf("%s cd - \n", strerror(errno));
		g_lob->exit_status = 0;
		return ;
	}
	printf("%s\n", home);
	home = getcwd(NULL, 0);
	change_env(home, "PWD");
	change_env(old_path, "OLDPWD");
	return ;
}

void	get_dir(char *home , char *old_path)
{
	if (chdir(home) == -1)
	{
		perror("Minishell");
		g_lob->exit_status = 1;
		return ;
	}
	home = getcwd(NULL, 0);
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
		old_path = getcwd(NULL, 0);
		if (!ft_strncmp(cmd[1], "~", 1) && ft_strlen(cmd[1]) == 1)
			chdir_home();
		else if (!ft_strncmp(cmd[1], "-", 1) && ft_strlen(cmd[1]) == 1)
			zig_zag(old_path);
		else if (old_path == NULL && !ft_strncmp(cmd[1], ".", 1) \
		&& ft_strlen(cmd[1]) == 1)
		{
			ft_putstr_fd("No such file or directory\n",2);
			g_lob->exit_status = 1;
			return ;
		}
		else
			get_dir(cmd[1], old_path);
	}
}
