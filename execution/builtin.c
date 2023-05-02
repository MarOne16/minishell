#include "../minishell.h"
char **empty_env(char **av)
{
	char **env;
	env = (char **)malloc(sizeof(char *) * 4);
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[1] = "SHLVL=1";
	env[2] = ft_strjoin("_=", av[0]);
	env[3] = NULL;
	return (env);
}

void ft_env(void)
{

	t_my_list *temp = (g_lob->env);
	if (temp)
	{
		while (temp)
		{
			printf("%s%s\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
}
void check_builtin(t_exe *all)
{
	char *s;
	char **n;
	extern char **environ;
	s = all->lakher[0];
	n = (char **)all->lakher;
	if (!s)
		return;
	if (!(ft_strncmp(s, "echo", 4)) && ft_strlen(s) == 4)
		ft_echo(n);
	else if (!(ft_strncmp(s, "cd", 2)) && ft_strlen(s) == 2)
		ft_chdir(n);
	else if ((!(ft_strncmp(s, "pwd", 3)) && ft_strlen(s) == 3) || (!(ft_strncmp(s, "PWD", 3)) && ft_strlen(s) == 3))
		ft_pwd(n);
	else if (!(ft_strncmp(s, "export", 6)) && ft_strlen(s) == 6)
		ft_exp(n);
	else if (!(ft_strncmp(s, "unset", 5)) && ft_strlen(s) == 5)
		ft_unset(n);
	else if ((!(ft_strncmp(s, "env", 3)) && ft_strlen(s) == 3) || (!(ft_strncmp(s, "ENV", 3)) && ft_strlen(s) == 3))
		ft_env();
	else if (!(ft_strncmp(s, "exit", 4)) && ft_strlen(s) == 4)
	{
		ft_exit(n);
	}
	else
	{
		ex_cmd(n);
	}
}
void check_builtin_multi(t_exe *all)
{
	char *s;
	char **n;
	extern char **environ;
	s = all->lakher[0];
	n = (char **)all->lakher;
	if (!s)
		exit(1);
	if (!(ft_strncmp(s, "echo", 4)) && ft_strlen(s) == 4)
	{
		ft_echo(n);
		exit(0);
	}
	else if (!(ft_strncmp(s, "cd", 2)) && ft_strlen(s) == 2)
	{
		ft_chdir(n);
		exit(0);
	}
	else if ((!(ft_strncmp(s, "pwd", 3)) && ft_strlen(s) == 3) || (!(ft_strncmp(s, "PWD", 3)) && ft_strlen(s) == 3))
	{
		ft_pwd(n);
		exit(0);
	}
	else if (!(ft_strncmp(s, "export", 6)) && ft_strlen(s) == 6)
	{
		ft_exp(n);
		exit(0);
	}
	else if (!(ft_strncmp(s, "unset", 5)) && ft_strlen(s) == 5)
	{
		ft_unset(n);
		exit(0);
	}
	else if ((!(ft_strncmp(s, "env", 3)) && ft_strlen(s) == 3) || (!(ft_strncmp(s, "ENV", 3)) && ft_strlen(s) == 3))
	{
		ft_env();
		exit(0);
	}
	else if (!(ft_strncmp(s, "exit", 4)) && ft_strlen(s) == 4)
	{
		ft_exit(n);
		exit(0);
	}
	else
	{
		mex_cmd(n);
	}
}
