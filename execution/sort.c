/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:54:14 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/14 15:47:35 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**list_to_array(t_my_list *exp)
{
	char		**list;
	int			i;
	int			count;
	t_my_list	*tmp;

	i = 0;
	count = 0;
	tmp = exp;
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tmp = exp;
	list = ft_malloc(sizeof(char *) * (count + 1), 0);
	while (i < count)
	{
		list[i] = ft_strjoin_mini(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	list[i] = NULL;
	return (list);
}

char	**sort_env(char **env)
{
	char	**list;
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = -1;
	list = env;
	while (list[++i])
	{
		j = i;
		while (list[++j])
		{
			k = 0;
			while (list[j][k] && list[i][k] && list[j][k] == list[i][k])
				k++;
			if (list[j][k] < list[i][k])
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
	return (list);
}

void	session(t_exe *all)
{
	int	size;

	size = size_prc(all);
	if (size == 1)
	{
		o_cmd(all);
	}
	if (size > 1)
	{
		lot_cmd(all, size);
	}
}
