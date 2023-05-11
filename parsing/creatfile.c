/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 03:04:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/02 15:41:47 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc(char *name)
{
	int		fd[2];
	char	*tmp;
	char	*content;

	sig_int();
	pipe(fd);
	while (1)
	{
		content = readline("> ");
		tmp = content;
		content = ft_strjoin_char(content, '\n', 1);
		free(tmp);
		if (content == NULL || !ft_strcmp(content, ft_strjoin_char(name, \
		'\n', 1)) || (g_lob->rd == 1 && rl_done == 1))
		{
			g_lob->rd = 0;
			break ;
		}
		write(fd[1], replace_vars(content), ft_strlen(replace_vars(content)));
	}
	close(fd[1]);
	return (fd[0]);
}

int	output_input_append(char *name, char type)
{
	int	fd;

	fd = 0;
	if (type == 'o')
	{
		fd = open(name, O_WRONLY | O_TRUNC);
		if (fd == -1 && errno == ENOENT)
			fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (type == 'i')
	{
		fd = open(name, O_RDONLY);
	}
	else if (type == 'a')
	{
		fd = open(name, O_RDWR | O_APPEND);
		if (fd == -1 && errno == ENOENT)
			fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	return (fd);
}

int	creat_fd(char type, char *name)
{
	int	fd;

	fd = 0;
	if (name[0] == '\t')
		return (-1);
	if (type == 'h')
	{
		fd = herdoc(name);
	}
	else if ((type == 'i') || (type == 'o') || (type == 'a'))
		fd = output_input_append(name, type);
	return (fd);
}

void	creat_file_2(t_cmd *tmp, t_fd **fd_list)
{
	int	fd;

	fd = creat_fd(get_type(tmp->cmd), tmp->next->cmd);
	if (fd == -1)
	{
		file_info(2, tmp->next->cmd);
		g_lob->exit_status = 1;
	}
	ft_lstadd_back_fd(fd_list, ft_lstnew_fd(get_type(tmp->cmd), fd));
}

void	creat_files(t_cmd *cmd, t_exe **exe)
{
	t_cmd	*tmp;
	t_exe	*tmp_exe;
	t_fd	*fd_list;

	if (cmd == NULL || exe == NULL)
		return ;
	tmp = cmd;
	fd_list = NULL;
	tmp_exe = *exe;
	while (tmp->next)
	{
		if (tmp->type == 1)
			creat_file_2(tmp, &fd_list);
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
