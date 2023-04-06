#include "minishell.h"

t_list	*ft_lstnew(char *name , char  *value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new -> name = name;
	new -> value = value;
	new -> next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst && !lst->next)
	{
		return (0);
	}
		temp = lst;
	while ( temp && temp -> next != NULL)
	{
		temp = temp -> next;
	}
	return (temp);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst && lst)
	{
		last = ft_lstlast(*lst);
		if(last)
		last -> next = new;
	}
	else
	{
		*lst = new;
	}
}
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int size_prc(t_prc ** allcmd)
{
	t_prc *tmp;
	int i;

	i = 0;
	tmp = *allcmd;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}