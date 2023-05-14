/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:16:42 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/14 21:37:11 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_env_plus(char *cmd, char *val)
{
	t_my_list	*e;

	e = var_env(cmd, ft_strlen(cmd));
	if (e)
	{
		if (e->value)
			e->value = ft_strjoin_mini(e->value, val);
	}
	else
	{
		ft_my_lstadd_back(&g_lob->env, ft_my_lstnew(cmd, val));
	}
}

void	put_env(char *cmd, char *val)
{
	t_my_list	*e;

	e = var_env(cmd, ft_strlen(cmd));
	if (e)
	{
		if (e->value && val)
			e->value = val;
	}
	else
	{
		if (val)
			ft_my_lstadd_back(&g_lob->env, ft_my_lstnew(cmd, val));
	}
}

void	put_in_exp(char *cmd, char *val)
{
	int			i;
	t_my_list	*s;

	i = 0;
	while (cmd[i])
		i++;
	if (cmd[i - 1] == '+')
		put_plus(cmd, val);
	else
	{
		s = var_exp(cmd, ft_strlen(cmd));
		if (s)
		{
			if (val)
				s->value = val;
		}
		else
		{
			if (val == NULL)
				ft_my_lstadd_back(&g_lob->exp, ft_my_lstnew(cmd, ""));
			else
				ft_my_lstadd_back(&g_lob->exp, ft_my_lstnew(cmd, val));
		}
		put_env(cmd, val);
	}
}

void	ad_exp(char **cmd)
{
	char	**tmp;
	char	*val;

	if (first_check(*cmd))
	{
		tmp = ft_my_split(*cmd, '=', 0);
		if (tmp[0])
		{
			if (check_var(tmp[0]))
			{
				val = check_value(ft_strdup_mini(*cmd, 0));
				put_in_exp(tmp[0], val);
			}
		}
		else
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			g_lob->exit_status = 1;
		}
	}
	else
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		g_lob->exit_status = 1;
	}
}

void	ft_exp(char **cmd)
{
	int		size;
	int		i;

	size = size_cmd(cmd);
	if (size == 1)
	{
		print_exp();
	}
	else if (size >= 2)
	{
		i = 1;
		while (cmd[i])
		{
			ad_exp(&cmd[i]);
			g_lob->environ = list_to_array(g_lob->exp);
			i++;
		}
	}
}
