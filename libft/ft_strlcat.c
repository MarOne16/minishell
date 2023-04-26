/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:51:39 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/27 02:07:34 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst,  char	*src, size_t n)
{
	size_t			i;
	size_t			s;
	size_t			d;

	i = 0;
	s = ft_strlen(src);
	if (dst == NULL && n == 0)
		return (s);
	d = ft_strlen(dst);
	if (d > n)
		return (n + s);
	while (d + 1 < n && src[i] != '\0')
	{
		dst[d] = src[i];
		d++;
		i++;
	}
	dst[d] = '\0';
	return (ft_strlen(dst) + ft_strlen(src + i));
}
