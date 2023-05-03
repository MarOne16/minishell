/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:03:29 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/03 16:01:07 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(void)
{
	t_my_list	*temp_env;

	temp_env = (glob->env);
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

	temp_env = (glob->env);
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

	temp_env = (glob->exp);
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
		glob->exit_status = 1;
	change = NULL;
	change = find_var_exp(modified, ft_strlen(modified));
	if (change)
		change->value = s;
	else
		glob->exit_status = 1;
}

void	chdir_home(void)
{
	char	*old_path;
	char	*home;

	old_path = getcwd(NULL, 0);
	home = get_home();
	if (home)
		home = ft_substr(home, 1, ft_strlen(home));
	else
	{
		home = getcwd(NULL, 0);
	}
	if (chdir(home) == -1)
	{
		printf("Can't Find home path : %s\n", strerror(errno));
		glob->exit_status = errno;
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
		if (home[0] == '=')
			home = ft_substr(home, 1, ft_strlen(home));
	}
	else
	{
		printf("%s\n", " OLDPWD not set");
		glob->exit_status = 1;
		return ;
	}
	if (chdir(home) == -1)
	{
		printf("%s cd - \n", strerror(errno));
		glob->exit_status = 1;
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
		glob->exit_status = errno;
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
			printf("%s\n", cmd[1]);
			glob->exit_status = 1;
			return ;
		}
		else
			get_dir(cmd[1], old_path);
	}
}
