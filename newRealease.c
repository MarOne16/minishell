#include "minishell.h"

void Creat_env(char **env)
{

	int i;
	char **tmp;
	t_list **listenv;
	i = 0;
	while (env[i])
		i++;
	listenv = (t_list **)malloc(sizeof(t_list *) * i + 1);
	*listenv = NULL;
	if (!listenv)
		perror("malloc");
	i = 0;
	while (env[i])
	{
		tmp = ft_my_split(env[i],'=');
		ft_lstadd_back(listenv,ft_lstnew(tmp[0],ft_strjoin("=",tmp[1])));
		i++;
	}
	glob->env = listenv;
}


char ** sort_env(char **env)
{
	char **list;
	char *tmp;
	int i = 0;
	int j = 0;
	int k = 0;
	list = env;
	while(list[i])
	{
		j = i + 1;
		while(list[j])
		{
			if(list[j][k] == list[i][k])
			{
					k++;
			}
			else if(list[j][k] < list[i][k])
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			else
			{
				k = 0;
				j++;
			}
		}
		i++;
	}
	return(list);
}
void Creat_exp(char **env)
{
	char ** s_env;
	char **tmp;
	t_list **list;
	int i = 0;
	s_env = sort_env(env);
	while (s_env[i])
		i++;
	list = (t_list **)malloc(sizeof(t_list *) * i + 1);
	if (!list)
		perror("malloc");
	i = 0;
	while (s_env[i])
	{
		tmp = ft_my_split(s_env[i],'=');
		if(tmp[0] && tmp[1])
			ft_lstadd_back(list, ft_lstnew(tmp[0],ft_strjoin("=",tmp[1])));
		i++;
	}
	(glob->exp) = list;

}
void session(t_prc **all)
{
	int size;
	size = size_prc(all);
	if(size == 1)
	{
			if(!(ft_strncmp((*all)->cmd->type,"word",4)))
			{
				check_builtin(all);
			}
			// else if(!(ft_strncmp((*all)->cmd->type,"token",5)))
			// 	check_token(all);	
	}
}