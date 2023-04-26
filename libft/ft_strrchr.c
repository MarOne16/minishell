/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:13:02 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/27 02:07:34 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( char *s, int c)
{
	char	*ss;
	int		i;

	ss = (char *)s;
	c = (char)c;
	i = 0;
	if (c != 0)
	{
		while (ss[i])
			i++;
		i--;
		while (i >= 0)
		{
			if (ss[i] == c)
				return (ss + i);
			i--;
		}
		return (NULL);
	}
	else
	{
		while (ss[i])
			i++;
		return (ss + i);
	}
}

// int main()
// {
// 	char *s = "hello marouane";
// 	char *r = "hello marouane";
// 	char * empty = (char*)calloc(1, 1);
// 	printf("%s\n",ft_strrchr(s,'t' + 256));
// 	// printf("%s",ft_strrchr(r,'e'));
// 	return 0;
// }
