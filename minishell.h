/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:37:03 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 15:09:51 by mqaos            ###   ########.fr       */
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

# include <errno.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# define MAX_VAR_LENGTH 1024

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

// list tools allcmd
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
// readline
void    feedlist(t_exe **all, char *input);
void	forcfree(t_cmd *input);
void	feedhashtable(int **hush, char *input);
int		typing(char *spl);
void	creat_var(t_exe **cmd);
void    sig_handler(int signum);
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
char	*add_spaces_around_operators(char *s, int *hash);
int		operatorscount(char *str, int *hash);

#endif // MINISHELL
