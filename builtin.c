#include "minishell.h"
int	ft_strncmp(char *s1,char *s2, size_t count)
{
	size_t	i;

	i = -1;
	while (++i < count && (s1[i] || s2[i]))
	{
		if (s2[i] != s1[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
void check_builtin(t_prc **all)
{
    char *s;
    t_cmd *n;

    s = (*all)->cmd->cmd;
    n = (*all)->cmd;
    if(!(ft_strncmp(s,"echo",4)) && ft_strlen(s) == 4)
        ft_echo(n);
    // else if(!(ft_strncmp(s,"cd",2)) && ft_strlen(s) == 2)
    //     ft_chdir(s);
    // else if(!(ft_strncmp(s,"pwd",3)) && ft_strlen(s) == 3)
    //     ft_pwd(s);
    // else if(!(ft_strncmp(s,"export",6)) && ft_strlen(s) == 6)
    //     ft_exp(s);
    // else if(!(ft_strncmp(s,"unset",3)) && ft_strlen(s) == 5)
    //     ft_unset(s);
    // else if(!(ft_strncmp(s,"env",3)) && ft_strlen(s) == 3)
    //     ft_env(s);
    // else if(!(ft_strncmp(s,"exit",4)) && ft_strlen(s) == 4)
    //     ft_exit(s);
    
}
void ft_echo(t_cmd *cmd)
{
    printf("%s\n",cmd->cmd);
}