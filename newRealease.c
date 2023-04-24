#include "minishell.h"

void Creat_env(char **env)
{
	int i;
	char **tmp;
	t_my_list *listenv;
	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	listenv = NULL;
	if (!listenv)
		perror("malloc");
	i = 0;
	while (env[i])
	{
		tmp = ft_my_split(env[i],'=');
		if(tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&listenv,ft_my_lstnew(tmp[0],ft_strjoin("=",tmp[1])));
		}
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
	char ** s_env = NULL;
	char **tmp;
	t_my_list *list = NULL;
	int i = 0;
	s_env = sort_env(env);
	while (s_env[i])
		i++;
	i = 0;
	while (s_env[i])
	{
		tmp = ft_my_split(s_env[i],'=');
		if(tmp && (*tmp) && tmp[0] && tmp[1])
			ft_my_lstadd_back(&list, ft_my_lstnew(tmp[0],ft_strjoin("=",tmp[1])));
		i++;
	}
	(glob->exp) = list;

}
int size_fd(t_fd *fd)
{
	int i = 0;
	while(fd)
	{
		i++;
		fd = fd->next;
	}
	return(i);
}

int in_fd(t_fd *tabfd)
{
	int i = 0;
	while(tabfd)
	{
		if(tabfd->type == 'i')
			i = tabfd->fd;
		tabfd = tabfd->next;
	}
	return(i);
}

int out_fd(t_fd *tabfd)
{
	int i = 0;
	while(tabfd)
	{
		if(tabfd->type == 'a' || tabfd->type == 'o')
			i = tabfd->fd;
		tabfd = tabfd->next;
	}
	return(i);
}
void session(t_exe *all)
{
    int size;
	int saved_stdin_fd;
	int saved_stdout_fd;
	int infd;
	int outfd;

    size = size_prc(all);

    if (size == 1)
	{
		infd = in_fd(all->fd);
		outfd = out_fd(all->fd);
        if(infd)
		{
			saved_stdin_fd = dup(STDIN_FILENO);
			dup2(infd,STDIN_FILENO);
		}
		if(outfd)
		{
			saved_stdout_fd = dup(STDOUT_FILENO);
			dup2(outfd,STDOUT_FILENO);
		}
		check_builtin(all);
		if(infd)
			dup2(saved_stdin_fd,STDIN_FILENO);
		if(outfd)
			dup2(saved_stdout_fd,STDOUT_FILENO);
    }
}