/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:54:14 by mbousouf          #+#    #+#             */
/*   Updated: 2023/05/09 19:04:05 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sort_exp(t_my_list **exp)
{
	t_my_list *current;
	t_my_list *ops; 
	t_my_list *min_node;
	char *temp_name;
	char *temp_value;
	
	current = *exp;
	min_node = current;
	ops = current->next;
	while (current != NULL) 
	{
		while (ops != NULL) 
		{
			if (cmpn(ops->name, min_node->name) < 0)
				min_node = ops;
			ops = ops->next;
		}
		if (min_node != current) 
		{
			temp_name = current->name;
			temp_value = current->value;
			current->name = min_node->name;
			current->value = min_node->value;
			min_node->name = temp_name;
			min_node->value = temp_value;
		}
		else
			break;
		current = current->next;
	}
}


int	cmpn(char *str, char *name)
{
	int	current;

	current = 0;
	while (str[current] != '\0' && name[current] != '\0')
	{
		if (str[current] != name[current])
		{
			return (str[current] - name[current]);
		}
		current++;
	}
	return (str[current] - name[current]);
}
char ** list_to_array(t_my_list *exp)
{
	char **list;
	int i;
	int count;
	t_my_list *tmp;

	i = 0;
	count = 0;
	tmp = exp;
	if(tmp == NULL)
		return(0);
	while(tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tmp = exp;
	list = malloc(sizeof(char *) * (count + 1));
	while(i < count)
	{
		list[i] = ft_strjoin(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	list[i] = NULL;
	return(list);
}
