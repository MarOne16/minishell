/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:18:39 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/14 23:22:40 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	struct s_tmp	tmp;
	char			*newstr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	tmp.i = -1;
	tmp.v = 0;
	tmp.n1 = (ft_strlen(s1));
	tmp.n2 = (ft_strlen(s2));
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	while (++tmp.i < tmp.n1)
		newstr[tmp.i] = s1[tmp.i];
	while (tmp.i <= (tmp.n1 + tmp.n2))
	{
		newstr[tmp.i] = s2[tmp.v];
		tmp.v++;
		tmp.i++;
	}
	return (newstr);
}
