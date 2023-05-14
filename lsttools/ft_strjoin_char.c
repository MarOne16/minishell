/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:22:18 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/12 22:38:17 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, int x)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	ft_memset(ptr, 0, size);
	if (x == 1)
		ft_lstadd_back(&g_lob->g_all, ft_lstnew(ptr));
	else
		ft_lstadd_back(&g_lob->g_exp, ft_lstnew(ptr));
	return (ptr);
}

char	*ft_strjoin_char(char *s, char c, int x)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s)
		return (0);
	len = ft_strlen(s) + 1;
	str = (char *)ft_malloc((sizeof(char) * (len + 1)), x);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
