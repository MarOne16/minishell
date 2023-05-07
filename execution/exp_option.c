/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:16:42 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/05 18:47:59 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_my_list	*var_exp(char *s, int size)
{
	t_my_list	*temp_env;

	temp_env = (g_lob->exp);
	while (temp_env)
	{
		if (!strncmp(s, temp_env->name, size))
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
