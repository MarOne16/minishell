/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdira.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:28:11 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/14 18:01:42 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	zig_zag(char *old_path)
{
	char	*home;

	home = NULL;
	if (find_var_env("OLDPWD", ft_strlen("OLDPWD")))
	{
		home = find_var_env("OLDPWD", ft_strlen("OLDPWD"))->value;
	}
	else
	{
		if (g_lob->old_pwd)
		{
			home = g_lob->old_pwd;
		}
	}
	if (chdir(home) == -1)
	{
		printf("OLD PWD not set : %s\n", strerror(errno));
		g_lob->exit_status = 0;
		return ;
	}
	printf("%s\n", home);
	change_env(home, "PWD");
	change_env(old_path, "OLDPWD");
	g_lob->old_pwd = old_path;
	g_lob->pwd = home;
}

void	get_dir(char *home, char *old_path)
{
	if (chdir(home) == -1)
	{
		perror("Minishell");
		g_lob->exit_status = 1;
		return ;
	}
	home = ft_getcwd();
	g_lob->pwd = home;
	g_lob->old_pwd = old_path;
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
		else if (old_path == NULL && ((!ft_strncmp(cmd[1], ".", 1) \
		&& ft_strlen(cmd[1]) == 1)))
		{
			ft_putstr_fd("No such file or directory\n", 2);
			g_lob->exit_status = 1;
			return ;
		}
		else
			get_dir(cmd[1], old_path);
	}
}

void	ex_cmd(char **cmd)
{
	char	*exe;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(cmd[0], '/'))
		{
			if (execve(cmd[0], cmd, g_lob->environ) == -1)
				exit(file_info(2, cmd[0]));
		}
		exe = pathcmd(cmd[0]);
		if (execve(exe, cmd, g_lob->environ) == -1)
		{
			ft_putstr_fd("command not found.\n", 2);
			exit(127);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
		g_lob->exit_status = WEXITSTATUS(status);
	}
}

void	mex_cmd(char **cmd)
{
	char	*exe;
	int		ex;

	if (ft_strchr(cmd[0], '/'))
	{
		if (execve(cmd[0], cmd, g_lob->environ) == -1)
		{
			ex = file_info(2, cmd[0]);
			exit(ex);
		}
	}
	exe = pathcmd(cmd[0]);
	if (execve(exe, cmd, g_lob->environ) == -1)
	{
		ft_putstr_fd("Minishell: multi_command not found\n", 2);
		exit(127);
	}
}
