/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:59:05 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 13:16:08 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	checkbefor(char *cmd, int i, int *hash)
{
	int	count;
	int	u;

	u = i;
	i--;
	count = 0;
	if ((i < 0) || (i >= (int)strlen(cmd)))
		return (0);
	while (u >= 0)
	{
		if (cmd[u] == '\'' && hash[u] == 0)
			count++;
		u--;
	}
	if (count % 2)
		return (1);
	while (cmd[i] && i >= 1)
	{
		if (i >= 1 && cmd[i] == '<' && cmd[i - 1] == '<' && \
		cmd[i] != 32 && hash[i] == 0)
			return (1);
		else if (cmd[i] == 32)
			i--;
		else
			return (0);
	}
	return (0);
}

size_t	get_new_length(char	*str)
{
	size_t	new_len;
	char	*var_start;
	char	*v_end;
	char	var_name[MAX_VAR_LENGTH];

	new_len = ft_strlen(str) + 1;
	while (*str != '\0')
	{
		if (*str == '$')
		{
			var_start = str + 1;
			v_end = str + 1;
			while (*v_end != '\0' && (*v_end == '_' || ft_isalnum(*v_end)))
				v_end++;
			if (v_end > var_start)
			{
				if ((int)(v_end - var_start) > (int)(sizeof(var_name) - 1))
					return (0);
				strncpy(var_name, var_start, (v_end - var_start));
				var_name[(v_end - var_start)] = '\0';
				if (getenv(var_name) != NULL)
					new_len += ft_strlen(getenv(var_name)) - (v_end - var_start);
				str = v_end;
			}
			else
				str++;
		}
		else
			str++;
	}
	return (new_len);
}

char* replace_vars(char* str)
{
	int *hash;
	
	feedhashtable(&hash, str);
	char* new_str = malloc(get_new_length(str));
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
					ft_memcpy(new_str_ptr, var_value, var_value_len);
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


