/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:59:05 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/13 00:21:16 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
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

char *removequote(char *str)
{
    char    *newstr;
    int     *hash;
    char    *temp;
    int     i;

    i = 0;
    hash = NULL;
    feedhashtable(&hash, str);
    newstr = ft_strdup("");
    while (str[i]) {
        if ((str[i] == '\"' || str[i] == '\'') && hash[i] == 0)
            i++;
        else {
            temp = newstr;
            newstr = ft_strjoin_char(newstr, str[i]);
            free(temp);
            i++;
        }
    }
    temp = newstr;
    newstr = ft_strjoin_char(newstr, str[i]);
    free(temp);
    free(hash); // Freeing the memory pointed to by hash
    return newstr;
}


char	*get_env_value(char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (environ[i] != NULL)
	{
		if ((ft_strncmpm(environ[i], name, (ft_strlen(environ[i]))) == 0) && \
		len)
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	checkbefor(char *cmd, int i, int *hash)
{
	int	count;
	int	u;

	u = i;
	i--;
	count = 0;
	while (u > 0)
	{
		if (cmd[u] == '\'' && hash[u] == 0)
			count++;
		u--;
	}
	if (count % 2)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i - 1] == '<' && \
		cmd[i - 2] != '<' && hash[i] == 0)
			return (1);
		else if (cmd[i] == 32)
			i--;
		else
			return (0);
	}
	return (0);
}

char	*replace_env_vars(char *str)
{
	int		i;
	int		j;
	char	*env_var;
	char	*env_value;
	char	*result;
	char	*temp;
	int		*hash = NULL;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	result = ft_strdup("");
	feedhashtable(&hash, str);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\"' && str[i + 1] != '?' && \
		str[i + 1] != ' ' && str[i + 1] && !checkbefor(str, i, hash))
		{
			j = i + 1;
			while (ft_isalnum(str[j]) || str[j] == '_')
				j++;
			env_var = ft_substr(str, i + 1, j - i - 1);
			env_value = get_env_value(env_var);
			if (env_value)
			{
				temp = result;
				result = ft_strjoin(result, env_value);
				free(temp);
				free(env_var);
				i = j;
				continue ;
			}
			i = j;
			free(env_var);
		}
		else
		{
			temp = result;
			result = ft_strjoin_char(result, str[i]);
			free(temp);
			i++;
		}
	}
	return (result);
}