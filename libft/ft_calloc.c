/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:56:59 by mqaos             #+#    #+#             */
/*   Updated: 2022/11/02 16:20:53 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	size_t			max;
	unsigned char	*cl;

	max = count * size;
	cl = malloc(max);
	i = 0;
	if (!cl)
	{
		return (NULL);
	}
	while (i < max)
	{
		cl[i] = '\0';
		i++;
	}
	return (cl);
}
