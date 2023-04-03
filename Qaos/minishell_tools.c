/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:07:36 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/03 02:24:50 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*ft_strdup( char *s1)
{
	size_t	i;
	char	*s11;

	s11 = (char *)malloc(sizeof(char) * ft_strlen(s1)+1);
	if (!s11)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s11[i] = s1[i];
		i++;
	}
	s11[i] = '\0';
	return (s11);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	r = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

long	ft_atoi(char *str)
{
	long	x;
	long	z;
	long	i;

	x = 1;
	z = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		z *= 10;
		z += str[i] - '0';
		i++;
	}
	return (z * x);
}

int	nb_c(char *str, char c, int *hash)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && hash[i] == 0)
		{
			count++;
			while ((str[i] && str[i] != c) || hash[i] == 1)
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	strlenword(char *s, char c, int i, int *hash)
{
	int	len;

	len = 0;
	while ((s[i] != c || hash[i] == 1) && s[i])
	{
		len++;
		i++;
	}
	return (len);
}


void	ft_free(char **strs, int j)
{
	while (j--)
		free(strs[j]);
	free(strs);
	return ;
}

char	**ft_split(char *s, char c, int *hush)
{
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (0x0);
	i = 0;
	j = -1;
	str = (char **)malloc((nb_c(s, c, hush) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++j < nb_c(s, c, hush))
	{
		while (s[i] == c && hush[i] == 0)
			i++;
		str[j] = ft_substr(s, i, strlenword(s, c, i, hush));
		if (!str[j])
		{
			ft_free(str, j + 1);
			return (0);
		}
		i += strlenword(s, c, i, hush);
	}
	str[j] = 0;
	return (str);
}
