/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:19:21 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/27 17:04:06 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	size_t			x;

	i = 0;
	x = -1;
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

// int main(int argc, char  *argv[])
// {
// 	char *s1 = "123";
// 	int *s2 = {1,2,3};
// 	printf("%d\n",ft_strncmp(s1,s2,0));
// 	printf("%d",strncmp(s1,s2,0));
// 	return 0;
// }
