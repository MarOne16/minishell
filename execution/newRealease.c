#include "../minishell.h"
#include <fcntl.h>

void Creat_env(char **env)
{
	int i;
	char **tmp;
	t_my_list *listenv;
	i = 0;
	listenv = NULL;
	while (env[i] != NULL)
	{
		i++;
	}
	i = 0;
	while (env[i])
	{
		tmp = ft_my_split(env[i], '=');
		if (tmp[0] && tmp[1])
		{
			ft_my_lstadd_back(&listenv, ft_my_lstnew(tmp[0], ft_strjoin("=", tmp[1])));
		}
		i++;
	}
	g_lob->env = listenv;
}

char **sort_env(char **env)
{
	char **list;
	char *tmp;
	int i = 0;
	int j = 0;
	int k = 0;
	list = env;
	while (list[i])
	{
		j = i + 1;
		while (list[j])
		{
			if (list[j][k] == list[i][k])
			{
				k++;
			}
			else if (list[j][k] < list[i][k])
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
	return (list);
}
void Creat_exp(char **env)
{
	char **s_env = NULL;
	char **tmp;
	t_my_list *list = NULL;
	int i = 0;
	s_env = sort_env(env);
	while (s_env[i])
		i++;
	i = 0;
	while (s_env[i])
	{
		tmp = ft_my_split(s_env[i], '=');
		if (tmp && (*tmp) && tmp[0] && tmp[1])
			ft_my_lstadd_back(&list, ft_my_lstnew(tmp[0], ft_strjoin("=", tmp[1])));
		i++;
	}
	(g_lob->exp) = list;
}
int size_fd(t_fd *fd)
{
	int i = 0;
	while (fd)
	{
		i++;
		fd = fd->next;
	}
	return (i);
}

int in_fd(t_fd *tabfd)
{
	int i = 0;
	while (tabfd)
	{
		if (tabfd->type == 'i' || tabfd->type == 'h')
			i = tabfd->fd;
		tabfd = tabfd->next;
	}
	return (i);
}

int ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("Cant' Not creat pipe ");
		exit(errno);
	}
	else
		return (0);
}

int ft_fork(void)
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Cant ' Not creat fork");
		exit(errno);
	}
	else
		return (pid);
}

int out_fd(t_fd *tabfd)
{
	int i = 0;
	while (tabfd)
	{
		if (tabfd->type == 'a' || tabfd->type == 'o')
			i = tabfd->fd;
		tabfd = tabfd->next;
	}
	return (i);
}
void o_cmd(t_exe *all)
{
	int saved_stdin_fd = dup(STDIN_FILENO);
	int saved_stdout_fd = dup(STDOUT_FILENO);
	int infd = in_fd(all->fd);
	int outfd = out_fd(all->fd);
	if (infd)
	{
		dup2(infd, STDIN_FILENO);
	}
	if (outfd)
	{
		dup2(outfd, STDOUT_FILENO);
	}
	check_builtin(all);
	if (infd)
	{
		dup2(saved_stdin_fd, STDIN_FILENO);
		close(saved_stdout_fd);
	}
	if (outfd)
	{
		dup2(saved_stdout_fd, STDOUT_FILENO);
		close(saved_stdin_fd);
	}
}
void m_cmd(t_exe *all)
{
	int saved_stdin_fd = dup(STDIN_FILENO);
	int saved_stdout_fd = dup(STDOUT_FILENO);
	int infd = in_fd(all->fd);
	int outfd = out_fd(all->fd);
	if (infd)
	{
		dup2(infd, STDIN_FILENO);
		printf("%d\n", infd);
	}
	if (outfd)
	{
		dup2(outfd, STDOUT_FILENO);
		printf("%d\n", outfd);
	}
	check_builtin_multi(all);
	if (infd)
	{
		close(infd);
		close(saved_stdout_fd);
		dup2(saved_stdin_fd, STDIN_FILENO);
	}
	if (outfd)
	{
		close(outfd);
		close(saved_stdin_fd);
		dup2(saved_stdout_fd, STDIN_FILENO);
	}
}

void lot_cmd(t_exe *all, int size)
{
	int fd[2];
	int pid;
	int i = 0;
	int input = dup(STDIN_FILENO);
	int *saved_in_fd = &input;
	int status = 0;
	puts("here");
	pid_t child_pids[size]; // array to store child process IDs
	while (all)
	{
		ft_pipe(fd);
		pid = ft_fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				close(fd[0]);
				close(fd[1]);
				dup2(*saved_in_fd, STDIN_FILENO);
				close(*saved_in_fd);
			}
			else if (i < size - 1)
			{
				close(fd[0]);
				close(*saved_in_fd);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
			}
			m_cmd(all);
		}
		else
		{
			close(fd[1]);
			// close(fd[0]);
			*saved_in_fd = fd[0];
			child_pids[i] = pid;
		}
		all = all->next;
		i++;
	}

	for (int j = 0; j < size; j++)
	{
		if (waitpid(child_pids[j], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				g_lob->exit_status = WEXITSTATUS(status);
		}
		else
		{
			if (all && all->lakher)
				fprintf(stderr, "Command terminated abnormally: %s\n", all->lakher[0]);
		}
	}
}
void session(t_exe *all)
{
	int size;
	size = size_prc(all);
	if (size == 1)
	{
		o_cmd(all);
	}
	if (size > 1)
	{
		lot_cmd(all, size);
	}
}
