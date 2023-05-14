/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:59:09 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/12 22:59:29 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	free_result(char **p, int nom)
{
	int	i;

	i = nom;
	if (!p)
		p = 0;
	else
		while (i > 0)
			free(p[i--]);
	free(p);
}

static int	numot(char *s, char c, int flags)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	if (flags && nb > 2)
		return (2);
	return (nb);
}

static char	**ft_get_next( char *s, char c, int len, int flags)
{
	char	**p;
	int		i;
	int		j;
	int		start;

	i = -1;
	j = 0;
	p = ft_malloc((len + 1) * sizeof(char *), 0);
	while (len && s[++i])
	{
		while (s[i] == c)
			i++;
		start = i;
		if (j + 1 == 2 && flags)
		{
			p[j++] = ft_substr_mini(s, start, ft_strlen(s) - start, 0);
			break ;
		}
		while (s[i] != c && s[i])
			i++;
		p[j++] = ft_substr_mini(s, start, (i - start), 0);
		start = i;
		len--;
	}
	return (p[j] = 0, p);
}

char	**ft_my_split(char *s, char c, int flags)
{
	char	**p;
	int		lenght;

	if (!s)
		return (0);
	lenght = numot(s, c, flags);
	p = ft_get_next(s, c, lenght, flags);
	if (!p)
	{
		free_result(p, numot(s, c, flags));
		return (0);
	}
	return (p);
}
