/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:04:23 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/14 18:37:47 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_new_ptr(char *str, char *new_str_ptr, t_tools t, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !checkbefor(str, i, t.hash))
		{
			t = get_variable_info(str, i);
			if (t.var_value != NULL)
				new_str_ptr = append_variable_value(t, new_str_ptr);
			else if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0' \
			|| str[i + 1] == '\'' || str[i + 1] == '\"'))
				*new_str_ptr++ = '$';
			else
				*new_str_ptr++ = '\t';
			i = t.v_e;
		}
		else
		{
			*new_str_ptr++ = str[i++];
		}
	}
	return (new_str_ptr);
}

char	*replace_vars(char	*str)
{
	struct s_tool	t;

	feedhashtable(&t.hash, str);
	t.new_str = ft_malloc(get_new_length(str), 1);
	t.new_str_ptr = t.new_str;
	t.i = 0;
	t.new_str_ptr = return_new_ptr(str, t.new_str_ptr, t, t.i);
	g_lob->exit_status = 0;
	return (*t.new_str_ptr = '\0', t.new_str);
}

char	*my_getenv(char *search)
{
	t_my_list	*rest;

	if (ft_strcmp(search, "?") == 0)
	{
		ft_putnbr_fd(g_lob->exit_status, 1);
		return (0);
	}
	rest = g_lob->env;
	while (rest)
	{
		if (ft_strcmp(search, rest->name) == 0)
			return (ft_substr_mini(rest->value, 1, ft_strlen(rest->value), 1));
		rest = rest->next;
	}
	return (NULL);
}
