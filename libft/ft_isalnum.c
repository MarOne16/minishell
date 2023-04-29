/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:46:55 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/29 11:14:49 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_special_char(char c)
{
	if (c == '!' || c == '@' || c == '#' || c == '%' || c == '^')
		return (1);
	else if (c == '&' || c == '*' || c == '(' || c == ')' || c == '-')
		return (1);
	else if (c == '+' || c == '=' || c == '{' || c == '}' || c == '[')
		return (1);
	else if (c == ']' || c == '|' || c == '\\' || c == ':' || c == ';')
		return (1);
	else if (c == '<' || c == '>' || c == ',')
		return (1);
	else if (c == '.' || c == '/' || c == '~' || c == '`')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || is_special_char(c)) == 1)
		return (1);
	else
		return (0);
}
