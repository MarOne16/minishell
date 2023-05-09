/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:57:56 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/09 16:12:44 by mbousouf         ###   ########.fr       */
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
			printf("declare -x %s%s\n", list->name, list->value);
			list = list->next;
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

	cmd = ft_substr(cmd, 0, ft_strlen(cmd) - 1);
	s = var_exp(cmd, ft_strlen(cmd));
	if (s != NULL)
	{
		if (s->value)
		{
			if (!ft_strncmp(s->value, "=", 0))
			{
				val = ft_substr(val, 1, ft_strlen(val) - 1);
			}
			s->value = ft_strjoin(s->value, val);
		}
	}
	else if (s == NULL)
	{
		ft_my_lstadd_back(&g_lob->exp, ft_my_lstnew(cmd, val));
	}
	put_env_plus(cmd, val);
}

void put_env_plus(char *cmd, char *val)
{
	t_my_list	*e;

	e = var_env(cmd, ft_strlen(cmd));
	if (e)
	{
		if (e->value)
			e->value = ft_strjoin(e->value, val);
	}
	else
	{
		ft_my_lstadd_back(&g_lob->env, ft_my_lstnew(cmd, val));
	}
}
void put_env(char *cmd, char *val)
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

void put_in_exp(char *cmd, char *val)
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

void ad_exp(char **cmd)
{
	char	**tmp;
	char	*val;

	if (first_check(*cmd))
	{
		tmp = ft_my_split(*cmd, '=');
		if (tmp[0])
		{
			if (check_var(tmp[0]))
			{
				val = check_value(*cmd);
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

void ft_exp(char **cmd)
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
		i = 0;
		cmd = &cmd[1];
		while (cmd[i])
		{
			ad_exp(&cmd[i]);
			sort_exp(&g_lob->exp);
			g_lob->environ = list_to_array(g_lob->exp);
			i++;
		}
	}
}
