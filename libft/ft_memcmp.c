/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:04:59 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/12 23:34:41 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( void *s1, void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (i < n)
	{
		if (c1[i] != c2[i])
		{
			return (c1[i] - c2[i]);
		}
		i++;
	}
	return (0);
}

// int main()
// {
// 	char s1[4]= {1,2,3};
// 	int s2[4] = {1,2,3};
// 	printf("%d\n",ft_memcmp(s1,s2,4));
// 	printf("%d",memcmp(s1,s2,4));
// 	return 0;
// }