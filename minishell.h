/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:37:03 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/28 11:18:00 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINISHELL)
# define MINISHELL

# include <errno.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# define MAX_VAR_LENGTH 1024

int ft_rl_done;

t_list	*g_all;
typedef struct s_fd
{
	char		type;
	int			fd;
	struct s_fd	*next;
	struct s_fd	*previus;
	
}				t_fd;

typedef struct s_exe
{
	void			**lakher;
	t_fd			*fd;
	struct s_exe	*next;
	struct s_exe	*previus;
}					t_exe;

typedef struct s_cmd
{
	int				type;
	char			*cmd;
	struct s_cmd	*next;
	struct s_cmd	*previus;
}					t_cmd;

struct s_asao
{
	char	*result;
	int		i;
	int		u;
	int		c;
	int		len;
	int		*hash;
}			t_asao;

typedef struct s_tool
{
	size_t	new_len;
	char	*vs;
	char	*ve;
	char	*new_str;
	char	*new_str_ptr;
	int		*hash;
	size_t	var_start;
	size_t	v_e;
	size_t	i;
	size_t	var_name_len;
	size_t	var_value_len;
	char	*var_value;
	char	var_name[MAX_VAR_LENGTH];
}			t_tools;

typedef struct s_my_list
{
	char			*name;
	char			*value;
	struct s_my_list	*next;
}t_my_list;

typedef struct s_global
{
	t_my_list *env;
	t_my_list *exp;
}	t_global;

t_global *glob;

//excute_tools
void Creat_env(char **env);
char ** sort_env(char **env);
void Creat_exp(char **env);
t_my_list	*ft_my_lstnew(char *name , char  *value);
int		ft_my_lstsize(t_my_list *lst);
t_my_list	*ft_my_lstlast(t_my_list *lst);
void	ft_my_lstadd_back(t_my_list **lst, t_my_list *new);
char	**ft_my_split(char *s, char c);
void	session(t_exe *all);
// int	ft_strncmp(char *s1,char *s2, size_t count);
void check_builtin(t_exe *all);
void ft_echo(char **cmd);
void ft_chdir(char **cmd);
void iter(int i);
void ft_exit(char **cmd);
char ** empty_env(char **av);
void print_exp();
void ft_exp(char **cmd);
void ft_pwd(char **pwd);
char *get_orgin(void);
t_my_list *find_var_env(char *s , int size);
t_my_list *find_var_exp(char *s , int size);
t_my_list *var_exp(char *s , int size);
char * ft_strncpy(char *src , char *dest ,int size);
t_my_list *var_env(char *s , int size);
void put_env_plus(char *cmd,char *val);
void ft_unset(char **cmd);
int check_unset_var(char *s);
void free_var_exp(char *s , int size);
void free_var_env(char *s , int size);
int size_prc(t_exe *allcmd);
int size_cmd(char **cmd);
char	*ft_strjoin(char  *s1, char  *s2);
void ex_cmd(char ** cmd);
// list tools allcmd
char	*ft_strjoin_char(char *s, char c);
char	*ft_strdup_mini( char *s1);
void	*ft_malloc(size_t size);
// list tools
t_exe	*ft_lstnewallcmd(void **cmd, void *fd);
void	ft_lstadd_frontcmd(t_exe **lst, t_exe *new);
void	ft_lstadd_backallcmd(t_exe **lst, t_exe *new);
t_exe	*ft_lstlastallcmd(t_exe *lst);
// list tools cmd
void	ft_lstadd_backcmd(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnewcmd(char *cmd, int type);
int		ft_lstsizetprc(t_cmd *lst);
t_cmd	*ft_lstlastcmd(t_cmd *lst);
// list tools fd
void	ft_lstadd_back_fd(t_fd **lst, t_fd *new);
t_fd	*ft_lstlast_fd(t_fd *lst);
t_fd	*ft_lstnew_fd(char type, int fd);
void	ft_lstadd_front_fd(t_fd **lst, t_fd *new);
// split tools
int		nb_c(char *s, char c,int *hash);
int		ft_strncmpm(char *s1,  char *s2, size_t n);
int		strlenword(char *s, char c, int i, int *hush);
void	ft_free(char **strs, int j);
char	**ft_splithash(char *s, char c, int *hush);
int		count_words(char *str, char c, int *hash, size_t len);
// replace_env_vars
char	*replace_vars(char* str);
int		checkbefor(char *cmd, int i, int *hash);
int		new_len(char **str, size_t new_len);
size_t	get_new_length(char	*str);
t_tools	get_variable_info(char *str, int i);
char	*append_variable_value(t_tools t, char *new_str_ptr);
char	*return_new_ptr(char *str, char *new_str_ptr, t_tools t, int i);
char	*replace_vars(char	*str);
// readline
void    sig_handler(int signum);
char	*ft_readline(void);
void	sig_here(int sig);
int		my_event(void);
void	sig_int(void);
// convert_to_char
int		sizechar(t_cmd *cmd);
char	*removequote(char *str);
void	table_lakher(t_cmd *cmd, t_exe **lakher);
char	get_type(char *str);
// creat_fd
void	creat_files(t_cmd *cmd, t_exe **exe);
int		herdoc(char *name);
int		output_input(char *name, char type);
int		append(char *name);
int		creat_fd(char type, char *name);
// parcing_tools
int		check_rid(t_cmd *cmdspl);
char	*add_spaces_around_operators(char *s, int *hash);
int		operatorscount(char *str, int *hash);
// parcing tools 2
char	*add_space_before_quote(char	*s);
int		typing(char *spl);
int		checkcmd(char *cmd, int *hash);
void	feedhashtable(int **hush, char *input);
void    feedlist(t_exe **all, char *input);

#endif // MINISHELL