/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:14:25 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/27 02:07:34 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( char *s, int c)
{
	char	*ss;
	int		i;

	ss = (char *)s;
	c = (char)c;
	i = 0;
	if (c != 0)
	{
		while (ss[i])
		{
			if (ss[i] == c)
				return (ss + i);
			i++;
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
// 	char *s = "hello marouane hhh ";
// 	char *r = "hello marouane hhh ";
// 	printf("%s\n",strchr(s,' '));
// 	printf("%s",ft_strchr(r,' '));
// 	return 0;
// }
