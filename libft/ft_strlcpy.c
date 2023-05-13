/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:19:52 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/12 23:33:35 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	m;

	i = 0;
	m = n;
	while (i + 1 < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < m)
		dst[i] = '\0';
	while (src[i])
	{
		i++;
	}
	return (i);
}

// int main(int argc, char  *argv[])
// {
// 	#include<string.h>
//     char r[5] = "bbbb";
//     char z[5] = "aaaa";
//     printf("%lu %s\n",strlcpy(r,z,3),r);
//     char a[5] = "bbbb";
//     char b[5] = "aaaa";
//     printf("%lu %s",ft_strlcpy(a,b,3),a);
//     return 0;
// }
