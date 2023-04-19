/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:59:05 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/19 01:02:22 by mqaos            ###   ########.fr       */
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
	free(s);
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
            i++;
        }
    }
    temp = newstr;
    newstr = ft_strjoin_char(newstr, str[i]);
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
		if ((ft_strncmpm(environ[i], name, (ft_strlen(environ[i]))) == 0) && len)
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
	while (u >= 0)
	{
		if (cmd[u] == '\'' && hash[u] == 0)
			count++;
		u--;
	}
	if (count % 2)
		return (1);
	while (cmd[i])
	{
		if (i >= 1 &&  cmd[i] == '<' && cmd[i - 1] == '<' && cmd[i] != 32 && hash[i] == 0)
			return (1);
		else if (cmd[i] == 32)
			i--;
		else
			return (0);
	}
	return (0);
}

static size_t get_new_length(char* str) {
    size_t new_len = ft_strlen(str) + 1;
    char* p = str;
    while (*p != '\0') {
        if (*p == '$') {
            char* var_start = p + 1;
            char* var_end = p + 1;
            while (*var_end != '\0' && (*var_end == '_' || ft_isalnum(*var_end))) {
                var_end++;
            }
            if (var_end > var_start) {
                char var_name[1024];
                size_t var_name_len = var_end - var_start;
                if (var_name_len > sizeof(var_name) - 1) {
                    return 0;
                }
                strncpy(var_name, var_start, var_name_len);
                var_name[var_name_len] = '\0';
                char* var_value = getenv(var_name);
                if (var_value != NULL) {
                    new_len += ft_strlen(var_value) - (var_end - var_start);
                }
                p = var_end;
            } else {
                p++;
            }
        } else {
            p++;
        }
    }
    return new_len;
}

char* replace_vars(char* str) {
    size_t new_len = get_new_length(str);
    int *hash ;
    feedhashtable(&hash, str);
    char* new_str = malloc(new_len);
    char* new_str_ptr = new_str;
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == '$' && !checkbefor(str, i, hash)) {
            size_t var_start = i + 1;
            size_t var_end = i + 1;
            while (str[var_end] != '\0' && (str[var_end] == '_' || ft_isalnum(str[var_end]))) {
                var_end++;
            }
            if (var_end > var_start) {
                char var_name[1024];
                size_t var_name_len = var_end - var_start;
                strncpy(var_name, str + var_start, var_name_len);
                var_name[var_name_len] = '\0';
                char* var_value = getenv(var_name);
                if (var_value != NULL) {
                    size_t var_value_len = strlen(var_value);
                    memcpy(new_str_ptr, var_value, var_value_len);
                    new_str_ptr += var_value_len;
                }
                else
                    *new_str_ptr++ = '\t';
                i = var_end;
            } else {
                *new_str_ptr++ = str[i++];
            }
        } else {
            *new_str_ptr++ = str[i++];
        }
    }
    *new_str_ptr = '\0';
    return new_str;
}


