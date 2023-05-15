/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:10:25 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/15 23:06:21 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**empty_env(char **av, char **env)
{
	char	*tmp;

	g_lob->if_free = 1;
	env = (char **)ft_malloc(sizeof(char *) * 6, 0);
	if (!env)
		return (NULL);
	tmp = ft_getcwd();
	env[0] = ft_strjoin_mini("OLDPWD=", "");
	env[1] = ft_strjoin_mini("PWD=", tmp);
	env[2] = ft_strdup_mini("SHLVL=1", 0);
	env[3] = ft_strjoin_mini("_=", av[0]);
	env[4] = ft_strjoin_mini("OLDPWD=", 0);
	env[5] = NULL;
	return (env);
}

char	*ft_strjoin_mini(char *s1, char *s2)
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
	ptr = (char *)ft_malloc((s2len + s1len + 1), 0);
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
