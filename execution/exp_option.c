/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:16:42 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/14 21:41:48 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_my_list	*var_exp(char *s, int size)
{
	t_my_list	*temp_env;

	(void)size;
	temp_env = (g_lob->exp);
	while (temp_env)
	{
		if (!ft_strcmp(s, temp_env->name))
		{
			return (temp_env);
		}
		temp_env = temp_env->next;
	}
	return (0);
}

t_my_list	*var_env(char *s, int size)
{
	t_my_list	*temp_env;

	temp_env = (g_lob->env);
	while (temp_env)
	{
		if (!ft_strncmp(s, temp_env->name, size))
		{
			return (temp_env);
		}
		temp_env = temp_env->next;
	}
	return (0);
}

char	*ft_strncpy(char *src, char *dest, int size)
{
	int	i;

	i = 0;
	if (!src || size <= 0)
		return (NULL);
	while (size)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	return (dest);
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
