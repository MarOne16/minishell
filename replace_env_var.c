/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:59:05 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/25 11:03:12 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

typedef struct s_tool
{
	size_t	new_len;
	char	*vs;
	char	*ve;
	char	*new_str;
	char	*new_str_ptr;
	int		*hash;
	size_t	var_start;
	size_t	var_end;
	size_t	i;
	size_t	var_name_len;
	size_t	var_value_len;
	char 	*var_value;
	char	var_name[MAX_VAR_LENGTH];
}			t_tools;

int	checkbefor(char *cmd, int i, int *hash)
{
	int	count;
	int	u;

	u = i + 1;
	i--;
	count = 0;
	if ((i < 0) || (i >= (int)strlen(cmd)))
		return (0);
	while (--u >= 0)
		if (cmd[u] == '\'' && hash[u] == 0)
			count++;
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

int	new_len(char **str, size_t new_len)
{
	struct s_tool	t;

	t.vs = *str + 1;
	t.ve = *str + 1;
	while (*t.ve != '\0' && (*t.ve == '_' || ft_isalnum(*t.ve)))
		t.ve++;
	if (t.ve > t.vs)
	{
		ft_memcpy(t.var_name, t.vs, t.ve - t.vs);
		t.var_name[t.ve - t.vs] = '\0';
		if (getenv(t.var_name) != NULL)
			new_len += ft_strlen(getenv(t.var_name));
		else
			new_len += 1;
		*str = t.ve;
	}
	else
		*str = t.ve;
	return (new_len);
}

size_t	get_new_length(char	*str)
{
	struct s_tool	t;

	t.new_len = ft_strlen(str) + 1;
	while (*str != '\0')
	{
		if (*str == '$')
			t.new_len += new_len(&str, t.new_len);
		else
			str++;
	}
	return (t.new_len);
}

char	*return_new_ptr(char *str, char *new_str_ptr, t_tools t, int i)
{
	while (str[i] != '\0') 
	{
		if (str[i] == '$' && !checkbefor(str, i, t.hash))
		{
			t.var_start = i + 1;
			t.var_end = i + 1;
			while (str[t.var_end] != '\0' && (str[t.var_end] == '_' || ft_isalnum(str[t.var_end])))
				t.var_end++;
			if (t.var_end > t.var_start)
			{
				t.var_name_len = t.var_end - t.var_start;
				strncpy(t.var_name, str + t.var_start, t.var_name_len);
				t.var_name[t.var_name_len] = '\0';
				t.var_value = getenv(t.var_name);
				if (t.var_value != NULL)
				{
					t.var_value_len = strlen(t.var_value);
					ft_memcpy(new_str_ptr, t.var_value, t.var_value_len);
					new_str_ptr += t.var_value_len;
				}
				else
					*new_str_ptr++ = '\t';
				i = t.var_end;
			}
			else
				*new_str_ptr++ = str[i++];
		}
		else
			*new_str_ptr++ = str[i++];
	}
	return (new_str_ptr);
}


char* replace_vars(char* str)
{
	struct s_tool	t;

	feedhashtable(&t.hash, str);
	t.new_str = malloc(get_new_length(str));
	t.new_str_ptr = t.new_str;
	t.i = 0;
	t.new_str_ptr = return_new_ptr(str, t.new_str_ptr, t, t.i);
	return (*t.new_str_ptr = '\0', t.new_str);
}


