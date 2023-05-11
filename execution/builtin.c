/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:10:25 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/10 22:51:47 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**empty_env(char **av)
{
	char	**env;

	env = (char **)malloc(sizeof(char *) * 4);
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[1] = "SHLVL=1";
	env[2] = ft_strjoin("_=", av[0]);
	env[3] = NULL;
	return (env);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1len;
	int		s2len;
	char	*ptr;
	int		j;

	j = -1;
	s1len = 0;
	s2len = 0;
	if (!s1 && !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *)malloc(s2len + s1len + 1);
	if (!ptr)
		return (NULL);
	while (++j <= s1len)
		ptr[j] = s1[j];
	j = 0;
	while (s2len)
	{
		ptr[s1len++] = s2[j++];
		s2len--;
	}
	ptr[s1len] = '\0';
	return (ptr);
}

void	ft_env(void)
{
	t_my_list	*temp;

	temp = g_lob->env;
	if (temp)
	{
		while (temp)
		{
			printf("%s%s\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
}

void	check_builtin(t_exe *all)
{
	char	*s;

	if (all->lakher == NULL || all->lakher[0] == NULL)
		return ;
	s = all->lakher[0];
	if (s[0] == '\0')
		return ;
	if (!(ft_strncmp(s, "echo", 4)) && ft_strlen(s) == 4)
		ft_echo((char **)all->lakher);
	else if (!(ft_strncmp(s, "cd", 2)) && ft_strlen(s) == 2)
		ft_chdir((char **)all->lakher);
	else if ((!(ft_strncmp(s, "pwd", 3)) && ft_strlen(s) == 3) \
	|| (!(ft_strncmp(s, "PWD", 3)) && ft_strlen(s) == 3))
		ft_pwd((char **)all->lakher);
	else if (!(ft_strncmp(s, "export", 6)) && ft_strlen(s) == 6)
		ft_exp((char **)all->lakher);
	else if (!(ft_strncmp(s, "unset", 5)) && ft_strlen(s) == 5)
		ft_unset((char **)all->lakher);
	else if ((!(ft_strncmp(s, "env", 3)) && ft_strlen(s) == 3) \
	|| (!(ft_strncmp(s, "ENV", 3)) && ft_strlen(s) == 3))
		ft_env();
	else if (!(ft_strncmp(s, "exit", 4)) && ft_strlen(s) == 4)
		ft_exit((char **)all->lakher);
	else
		ex_cmd((char **)all->lakher);
}

void	check_builtin_multi(t_exe *all)
{
	char	*s;

	if (all->lakher == NULL || all->lakher[0] == '\0')
		exit(1);
	s = all->lakher[0];
	if (s[0] == '\0')
		return ;
	if (!(ft_strncmp(s, "echo", 4)) && ft_strlen(s) == 4)
	{
		ft_echo((char **)all->lakher);
		exit(0);
	}
	else if (!(ft_strncmp(s, "cd", 2)) && ft_strlen(s) == 2)
	{
		ft_chdir((char **)all->lakher);
		exit(0);
	}
	else if ((!(ft_strncmp(s, "pwd", 3)) && ft_strlen(s) == 3) \
	|| (!(ft_strncmp(s, "PWD", 3)) && ft_strlen(s) == 3))
	{
		ft_pwd((char **)all->lakher);
		exit(0);
	}
	else
		extra_bluitin_multi((char **)all->lakher, s);
}

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
