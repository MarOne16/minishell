/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdub_mini.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:34:30 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/12 23:32:55 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_mini( char *s1, int x)
{
	size_t	i;
	char	*s11;

	s11 = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + 1), x);
	if (!s11)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s11[i] = s1[i];
		i++;
	}
	s11[i] = '\0';
	return (s11);
}

char	*ft_substr_mini(char *s, unsigned int start, size_t len, int x)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup_mini("", x));
	str = (char *)ft_malloc(sizeof(char) * (len + 1), x);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
