/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:01:53 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/16 16:24:52 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extra_bluitin_multi(char **n, char *s)
{
	if (!(ft_strncmp(s, "export", 6)) && ft_strlen(s) == 6)
	{
		ft_exp(n);
		exit(0);
	}
	else if (!(ft_strncmp(s, "unset", 5)) && ft_strlen(s) == 5)
	{
		ft_unset(n);
		exit(0);
	}
	else if ((!(ft_strncmp(s, "env", 3)) && ft_strlen(s) == 3) \
	|| (!(ft_strncmp(s, "ENV", 3)) && ft_strlen(s) == 3))
	{
		ft_env();
		exit(0);
	}
	else if (!(ft_strncmp(s, "exit", 4)) && ft_strlen(s) == 4)
	{
		ft_exit(n);
		exit(0);
	}
	else
		mex_cmd(n);
}

void	zig_zag(char *old_path)
{
	char	*home;

	if (find_var_env("OLDPWD", ft_strlen("OLDPWD")))
	{
		home = find_var_env("OLDPWD", ft_strlen("OLDPWD"))->value;
		if (home[0] == '=')
			home = ft_substr_mini(home, 1, ft_strlen(home), 0);
	}
	else
	{
		printf("%s\n", " OLDPWD not set");
		g_lob->exit_status = 1;
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

void	get_dir(char *home, char *old_path)
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
			ft_putstr_fd("No such file or directory\n", 2);
			g_lob->exit_status = 1;
			return ;
		}
		else
			get_dir(cmd[1], old_path);
	}
}
