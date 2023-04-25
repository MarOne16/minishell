/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:59:05 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/25 15:08:19 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_tools	get_variable_info(char *str, int i)
{
	t_tools	t;

	t.var_start = i + 1;
	t.v_e = i + 1;
	while (str[t.v_e] && (str[t.v_e] == '_' || ft_isalnum(str[t.v_e])))
	{
		t.v_e++;
	}
	if (t.v_e > t.var_start)
	{
		t.var_name_len = t.v_e - t.var_start;
		strncpy(t.var_name, str + t.var_start, t.var_name_len);
		t.var_name[t.var_name_len] = '\0';
		t.var_value = getenv(t.var_name);
	}
	return (t);
}

char	*append_variable_value(t_tools t, char *new_str_ptr)
{
	t.var_value_len = strlen(t.var_value);
	ft_memcpy(new_str_ptr, t.var_value, t.var_value_len);
	new_str_ptr += t.var_value_len;
	return (new_str_ptr);
}
