/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:59:05 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/04 06:39:47 by mqaos            ###   ########.fr       */
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


char *get_env_value(char *name)
{
    extern char **environ;
    int i;
    size_t len;

    len = ft_strlen(name);
    i = 0;
    while (environ[i] != NULL)
    {
        if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            // char *value = environ[i] + len + 1;
            // char *result = ft_strjoin(name, "=");
            // result = ft_strjoin_char(result, '"');
            // result = ft_strjoin(result, value);
            // result = ft_strjoin_char(result, '"');
            // return result;
			return (environ[i] + len + 1);
        }
        i++;
    }
    return NULL;
}

int	checkbefor(char *cmd, int i)
{
	int count;
	int u;

	if (i < 2)
		return (0);
	u = i;
	i--;
	count = 0;
	// while (u > 0)
	// {
	// 	if (cmd[u] == '\'')
	// 		count++;
	// 	u--;
	// }
	// if (count % 2)
	// 	return (1);
	while (cmd[i])
	{
		if (cmd[i] == '>' && cmd[i - 1] == '>')
			return (1);
		else if (cmd[i] == 32)
			i--;
		else
			return (0);
	}
	return(0);
	
}

char	*replace_env_vars(char *str)
{
	int		i;
	int		j;
	char	*env_var;
	char	*env_value;
	char	*result;
	char	*temp;

	i = 0;
	j = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && !checkbefor(str, i))
		{
			j = i + 1;
			while (ft_isalnum(str[j]))
				j++;
			env_var = ft_substr(str, i + 1, j - i - 1);
			env_value = get_env_value(env_var);
			if (env_value != NULL)
			{
				temp = result;
				result = ft_strjoin(result, env_value);
				free(temp);
				free(env_var);
				i = j;
				continue;
			}
			free(env_var);
			i = j;
		}
		temp = result;
		result = ft_strjoin_char(result, str[i]);
		free(temp);
		i++;
	}
	return (result);
}