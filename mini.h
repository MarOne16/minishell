/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:12:29 by mbousouf          #+#    #+#             */
/*   Updated: 2023/04/03 01:52:11 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef MINI_H
# define MINI_H
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#endif


typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}t_list;

typedef struct s_global
{
	t_list **env;
	t_list **exp;
}	t_global;

t_global glob;

t_list	*ft_lstnew(char *name , char  *value);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);