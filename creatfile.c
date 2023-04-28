/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 03:04:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/26 18:45:05 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int herdoc(char *name)
{
	int fd[2];
	char *content;

	pipe(fd);
	while ((content = readline("haerdoc>")))
	{
		if (strcmp(content, name) == 0)
			break ;
		if ((size_t)write(fd[1], content, ft_strlen(content)) != ft_strlen(content))
		{
			printf("\nError writing to file.\n");
			close(fd[1]);
			return (1);
		}
	}
	close(fd[1]);
	return (fd[0]);
}

int input(char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	return (fd);
}

int	output_input(char *name, char type)
{
	int fd;

	if (type == 'o')
		fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(name, O_RDONLY);
	return (fd);
}

int append(char *name)
{
	int fd;

	fd = open(name, O_RDWR | O_APPEND);
	if (fd == -1 && errno == ENOENT)
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	return (fd);
}

int	creat_fd(char type, char *name)
{
	int fd;

	fd = 0;
	if (type == 'a')
		fd = append(name);		
	else if (type == 'h')
		fd = herdoc(name);
	else if ((type == 'i') || (type == 'o'))
		fd = output_input(name, type);
	else
		return(fd);
	return (fd);
}
char	get_type(char *str)
{
	if (ft_strcmp(str, ">>") == 0)
		return ('a');
	else if (ft_strcmp(str, "<<") == 0)
		return ('h');
	else if (ft_strcmp(str, "<") == 0)
		return ('i');
	else if (ft_strcmp(str, ">") == 0)
		return ('o');
	else
		return ('x');
}

void creat_files(t_cmd *cmd, t_exe **exe)
{
	t_cmd *tmp;
	t_exe *tmp_exe;
	t_fd *fd_list;
	int fd;

	if (!cmd || !exe)
		return ;
	tmp = cmd;
	fd_list = NULL;
	tmp_exe = *exe;
	while (tmp->next)
	{
		if(tmp->type == 1)
		{
			fd = creat_fd(get_type(tmp->cmd), tmp->next->cmd);
			if (fd == -1)
			{
				printf("\nError opening file.\n");
				return ;
			}
			ft_lstadd_back_fd(&fd_list, ft_lstnew_fd(get_type(tmp->cmd), fd));
		}
		else if (tmp->type == 2)
		{
			tmp_exe->fd = fd_list;
			fd_list = NULL;
			tmp_exe = tmp_exe->next;
		}
		tmp = tmp->next;
	}
	tmp_exe->fd = fd_list;
}
