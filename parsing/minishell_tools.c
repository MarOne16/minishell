/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:07:36 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/28 09:38:32 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	nb_c(char *str, char c, int *hash)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && hash[i] == 0)
		{
			count++;
			while ((str[i] && str[i] != c) || hash[i] == 1)
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	strlenword(char *s, char c, int i, int *hash)
{
	int	len;

	len = 0;
	while ((s[i] != c || hash[i] == 1) && s[i])
	{
		len++;
		i++;
	}
	return (len);
}


void	ft_free(char **strs, int j)
{
	while (j--)
		free(strs[j]);
	free(strs);
	return ;
}

char	**ft_splithash(char *s, char c, int *hush)
{
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (0x0);
	i = 0;
	j = -1;
	str = (char **)malloc((nb_c(s, c, hush) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++j < nb_c(s, c, hush))
	{
		while (s[i] == c && hush[i] == 0)
			i++;
		str[j] = ft_substr(s, i, strlenword(s, c, i, hush));
		if (!str[j])
		{
			ft_free(str, j + 1);
			return (0);
		}
		i += strlenword(s, c, i, hush);
	}
	str[j] = 0;
	return (str);
}

int	ft_strncmpm(char *s1, char *s2, size_t n)
{
	size_t			i;
	size_t			x;

	i = 0;
	x = -1;
	while (s1[++x] != '=' && s1[x])
	{

	}
	if (x < ft_strlen(s2))
		return (1);
	while ((s1[i] || s2[i]) && s1[i] != '=' && i <= n)
	{
		if (s2[i] != s1[i])
			return (1);
		i++;
	}
	return (0);
}
