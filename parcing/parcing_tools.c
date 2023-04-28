/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:13:19 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/28 09:38:32 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	operatorscount(char *str, int *hash)
{
	int	i;
	int	count;
	int	c;

	c = 0;
	i = -1;
	feedhashtable(&hash, str);
	while (str[++i])
	{
		count = 0;
		while (str[i] && (str[i] == '<' || str[i] == '>') && hash[i] == 0)
		{
			count++;
			i++;
		}
		if ((count == 1 || count == 2))
			c++;
		else if (count > 2)
			return (1337);
	}
	return (c);
}

char	*add_spaces_around_pipe(char *s, int *hash)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup_mini("");
	feedhashtable(&hash, s);
	while (s[i])
	{
		if (s[i] == '|' && hash[i] == 0)
		{
			result = ft_strjoin_char(result, ' ');
			result = ft_strjoin_char(result, s[i++]);
			result = ft_strjoin_char(result, ' ');
		}
		else
			result = ft_strjoin_char(result, s[i++]);
	}
	return (result);
}

char	*add_spaces_around_redirection(char *s, int *hash)
{
	struct s_asao	t;

	t.i = 0;
	t.result = ft_strdup_mini("");
	while (s[t.i])
	{
		t.u = t.i - 1;
		t.c = 0;
		while (s[++t.u] && (s[t.u] == '<' || s[t.u] == '>') && hash[t.u] == 0)
			t.c++;
		if (t.c == 1 || t.c == 2)
		{
			t.result = ft_strjoin_char(t.result, ' ');
			while (s[t.i] && (s[t.i] == '>' || s[t.i] == '<'))
				t.result = ft_strjoin_char(t.result, s[t.i++]);
			t.result = ft_strjoin_char(t.result, ' ');
		}
		else if (t.c > 2)
			while (s[t.i] && t.c--)
				t.result = ft_strjoin_char(t.result, s[t.i++]);
		else
			t.result = ft_strjoin_char(t.result, s[t.i++]);
	}
	return (t.result);
}

char	*add_spaces_around_operators(char *s, int *hash)
{
	char	*result;
	char	*tmp;

	feedhashtable(&hash, s);
	tmp = add_spaces_around_pipe(s, hash);
	feedhashtable(&hash, tmp);
	result = add_spaces_around_redirection(tmp, hash);
	return (result);
}

int	check_rid(t_cmd *cmdspl)
{
	t_cmd	*reset2;

	reset2 = cmdspl;
	while (reset2)
	{
		if (reset2->type == 1 && \
		(!reset2->next || (reset2->next->type != 0)))
			return (1);
		else if (reset2->type == 2 && (!reset2->next || \
		(reset2->next->type == 2)))
			return (1);
		reset2 = reset2->next;
	}
	return (0);
}
