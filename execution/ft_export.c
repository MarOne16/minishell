/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:57:56 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/12 23:38:09 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_exp(void)
{
	t_my_list	*list;

	if (g_lob->exp)
	{
		list = (g_lob->exp);
		while (list)
		{
			if ((list)->value)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd((list)->name, 1);
				ft_putstr_fd((list)->value, 1);
				ft_putstr_fd("\n", 1);
			}
			else
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd((list)->name, 1);
				ft_putstr_fd("\n", 1);
			}
			list = (list)->next;
		}
	}
}

int	check_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '_')
			i++;
		else
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			g_lob->exit_status = 1;
			return (0);
		}
		while (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '+')
		{
			if (s[i] == '+' && s[i + 1] != '\0')
			{
				ft_putstr_fd(" not a valid identifier\n", 2);
				g_lob->exit_status = 1;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

char	*check_value(char *s)
{
	int	i;
	int	cmdsize;

	i = 0;
	cmdsize = 0;
	cmdsize = ft_strlen(s);
	if (cmdsize == 0)
		return (NULL);
	while ((s[i] != '=') && s[i])
		i++;
	if (s[i] == '\0')
		return (NULL);
	s = &s[i];
	return (s);
}

int	first_check(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '=')
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	put_plus(char *cmd, char *val)
{
	t_my_list	*s;

	cmd = ft_substr_mini(cmd, 0, ft_strlen(cmd) - 1, 0);
	s = var_exp(cmd, ft_strlen(cmd));
	if (s != NULL)
	{
		if (s->value)
		{
			if (!ft_strncmp(s->value, "=", 0))
			{
				val = ft_substr_mini(val, 1, ft_strlen(val) - 1, 0);
			}
			s->value = ft_strjoin_mini(s->value, val);
		}
	}
	else if (s == NULL)
	{
		ft_my_lstadd_back(&g_lob->exp, ft_my_lstnew(cmd, val));
	}
	put_env_plus(cmd, val);
}
