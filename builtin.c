#include "minishell.h"
char ** empty_env(char **av)
{
    char **env;
    env = (char **)malloc(sizeof(char *) * 4);
    env[0] = ft_strjoin("PWD=",getcwd(NULL,0));
    env[1] = "SHLVL=1";
    env[2] = ft_strjoin("_=",av[0]);
    env[3] = NULL;
    return(env);
}
// int	ft_strncmp(char *s1,char *s2, size_t count)
// {
// 	size_t	i;

// 	i = -1;
// 	while (++i < count && (s1[i] || s2[i]))
// 	{
// 		if (s2[i] != s1[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	}
// 	return (0);
// }

// char	*ft_strjoin(char  *s1, char  *s2)
// {
// 	int	s1len;
// 	int	s2len;
// 	char	*ptr;
// 	int		j;

// 	j = -1;
//     s1len=0;
//     s2len=0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	    s1len = ft_strlen(s1);
// 	    s2len = ft_strlen(s2);
// 		ptr = (char *)malloc(s2len + s1len + 1);
// 		if (!ptr)
// 			return (NULL);
// 		while( ++j <= s1len)
// 			ptr[j] = s1[j];
// 		j=0;
// 		while (s2len)
// 		{
// 			ptr[s1len++] = s2[j++];
// 				s2len--;
// 		}
// 		ptr[s1len] = '\0';
// 		return (ptr);
// }

void ft_env()
{
    t_my_list *temp = (glob->env);
    if(temp)
    {
        while(temp)
        {
            printf("%s%s\n",temp->name,temp->value);
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
    if(!(ft_strncmp(s,"echo",4)) && ft_strlen(s) == 4)
        ft_echo(n);
    else if(!(ft_strncmp(s,"cd",2)) && ft_strlen(s) == 2)
        ft_chdir(n);
    else if((!(ft_strncmp(s,"pwd",3)) && ft_strlen(s) == 3) || (!(ft_strncmp(s,"PWD",3)) && ft_strlen(s) == 3))
        ft_pwd(n);
    else if(!(ft_strncmp(s,"export",6)) && ft_strlen(s) == 6)
        ft_exp(n);
    else if(!(ft_strncmp(s,"unset",3)) && ft_strlen(s) == 5)
        ft_unset(n);
    else if((!(ft_strncmp(s,"env",3)) && ft_strlen(s) == 3) || (!(ft_strncmp(s,"ENV",3)) && ft_strlen(s) == 3))
        ft_env();
    else if(!(ft_strncmp(s,"exit",4)) && ft_strlen(s) == 4)
    {
        ft_exit(n);
    }
    
}

