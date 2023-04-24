/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_char_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:40:48 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 12:08:00 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*removequote(char *str)
{
	char	*newstr;
	int		*hash;
	int		i;

	i = 0;
	hash = NULL;
	feedhashtable(&hash, str);
	newstr = ft_strdup("");
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && hash[i] == 0)
			i++;
		else
		{
			newstr = ft_strjoin_char(newstr, str[i]);
			i++;
		}
	}
	newstr = ft_strjoin_char(newstr, str[i]);
	return (newstr);
}

int	sizechar(t_cmd *cmd)
{
	t_cmd	*rest;
	int		i;

	i = 0;
	rest = cmd;
	if (rest && rest->type == 2)
		rest = rest->next;
	while (rest)
	{
		if (rest->type == 2)
			break ;
		else if (rest->type == 1)
			rest = rest->next->next;
		else
		{
			rest = rest->next;
			i++;
		}
	}
	return (i);
}

void	table_lakher(t_cmd *cmd, t_exe **lakher)
{
	char	**spl;
	t_cmd	*rest;
	int		i;

	i = 0;
	rest = cmd;
	spl = malloc((sizechar(rest) + 1) * sizeof(char *));
	if (rest && rest->type == 2)
		rest = rest->next;
	while (rest && rest->type != 2)
	{
		if (rest->next && rest->type == 1)
			rest = rest->next->next;
		else
		{
			spl[i++] = removequote(rest->cmd);
			rest = rest->next;
		}
	}
	spl[i] = NULL;
	ft_lstadd_backallcmd(lakher, ft_lstnewallcmd((void **)spl, NULL));
	if (rest && rest->next)
		table_lakher(rest, lakher);
}

char	get_type(char *str)
{
	if (ft_strcmp(str, ">>") == 0)
		return ('a');
	else if (ft_strcmp(str, "<<") == 0)
		return ('h');
	else if (ft_strcmp(str, "<") == 0)
		return ('i');
	else if (ft_strcmp(str, ">") == 0)
		return ('o');
	else
		return ('x');
}
