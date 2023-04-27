/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:35:20 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/27 17:03:41 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *h, char *n, size_t len)
{
	char	*h1;
	size_t	i;
	size_t	k;

	h1 = (char *)h;
	i = 0;
	if (n[0] == '\0')
		return (h1);
	while (h1[i])
	{
		k = 0;
		while (h1[i + k] == n[k] && (i + k) < len)
		{
			if (n[k + 1] == '\0')
				return (h1 + i);
			k++;
		}
		if (n[k] == '\0')
			return (h1 + i);
		i++;
	}	
	return (0);
}
// int main()
// {
// 	char	*str;
//     if (!(str = ft_strnstr("lorem ipsum dolor sit amet", "dol", 30)))
//         printf("NULL");
//     else
//         printf("%s",str);
// 	return 0;
// }