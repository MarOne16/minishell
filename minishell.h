/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:37:03 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/16 03:21:48 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINISHELL)
# define MINISHELL

# define AC_BLACK "\x1b[30m"
# define AC_RED "\x1b[31m"
# define AC_GREEN "\x1b[32m"
# define AC_YELLOW "\x1b[33m"
# define AC_BLUE "\x1b[34m"
# define AC_MAGENTA "\x1b[35m"
# define AC_CYAN "\x1b[36m"
# define AC_WHITE "\x1b[37m"
# define AC_NORMAL "\x1b[m"

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <ctype.h>
# include <stdio.h>
# include <limits.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env
{
	char **env;
}t_env;

typedef struct s_cmd
{
	char			*type;
	char			*cmd;
	struct s_cmd	*next;
	struct s_cmd	*previus;
}				t_cmd;

typedef struct s_prc
{
	char			*allcmd;
	t_cmd			*cmd;
	struct s_prc	*next;
	struct s_prc	*previus;
}					t_prc;

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

t_global *glob;

//excute_tools
void Creat_env(char **env);
char ** sort_env(char **env);
void Creat_exp(char **env);
t_list	*ft_lstnew(char *name , char  *value);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	**ft_my_split(char *s, char c);
void	session(t_prc ** all);
int	ft_strncmp(char *s1,char *s2, size_t count);
void check_builtin(t_prc **all);
void ft_echo(t_cmd *cmd);
void ft_chdir(t_cmd *cmd);
void iter(int i);
void ft_exit(t_cmd *cmd);
char ** empty_env(char **av);
void print_exp();
void ft_exp(t_cmd *cmd);
void ft_pwd(t_cmd *pwd);
char *get_orgin(void);
t_list *find_var_env(char *s , int size);
t_list *find_var_exp(char *s , int size);
t_list *var_exp(char *s , int size);
char * ft_strncpy(char *src , char *dest ,int size);
t_list *var_env(char *s , int size);
void put_env_plus(char *cmd,char *val);


// list tools
t_prc	*ft_lstnewallcmd(char *allcmd, t_cmd *cmd);
t_cmd	*ft_lstnewcmd(char *cmd, char *type);
void	ft_lstadd_front(t_prc **lst, t_prc *new);
t_prc	*ft_lstlastallcmd(t_prc *lst);
t_cmd	*ft_lstlastcmd(t_cmd *lst);
void	ft_lstadd_backallcmd(t_prc **lst, t_prc *new);
void	ft_lstadd_backcmd(t_cmd **lst, t_cmd *new);
int size_prc(t_prc ** allcmd);
int size_cmd(t_cmd *cmd);
// atoi & split tools
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);
int	nb_c(char *s, char c,int *hash);
int		strlenword(char *s, char c, int i, int *hush);
void	ft_free(char **strs, int j);
char	**ft_split(char *s, char c, int *hush);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
int count_words(char *str, char c, int *hash, size_t len);
char **ft_split_hash(char *str, char c, int *hash, size_t len);
char	*ft_strjoin(char  *s1, char  *s2);

// readline
void    feedlist(t_prc **all, char *input);
void	feedhashtable(int *hush, char *input);
int		operatorscount(char *str, int *hash);
char	*add_spaces_around_operators(char *s, int *hash);
char	*typing(char *spl);
char	*getvariable(char *input);
int		getsize(char *str);
char	*remplace(char *old, char **env);


// typedef struct s_data
// {
// 	t_env env;
// }t_data;
#endif // MINISHELL
