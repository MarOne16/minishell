/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:37:03 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/16 03:19:29 by mqaos            ###   ########.fr       */
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
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

char **environ;

typedef struct s_env
{
	char **env;
	int	*fd;
}t_env;

typedef struct s_cmd
{
	int				type;
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

// list tools
t_prc	*ft_lstnewallcmd(char *allcmd, t_cmd *cmd);
t_cmd	*ft_lstnewcmd(char *cmd, int type);
void	ft_lstadd_frontcmd(t_prc **lst, t_prc *new);
int		ft_lstsizetprc(t_prc *lst);
t_cmd	*ft_lstlastcmd(t_cmd *lst);
t_cmd	*ft_lstlastcmd(t_cmd *lst);
void	ft_lstadd_backallcmd(t_prc **lst, t_prc *new);
void	ft_lstadd_backcmd(t_cmd **lst, t_cmd *new);
// atoi & split tools
int		nb_c(char *s, char c,int *hash);
int		ft_strncmpm(char *s1,  char *s2, size_t n);
int		strlenword(char *s, char c, int i, int *hush);
void	ft_free(char **strs, int j);
char	**ft_splithash(char *s, char c, int *hush);
int		count_words(char *str, char c, int *hash, size_t len);
// replace_env_vars
char* replace_vars(char* str);
char	*ft_strjoin_char(char *s, char c);
char	*removequote(char *str);
// readline
void    feedlist(t_prc **all, char *input);
void	forcfree(t_prc **input);
void	feedhashtable(int **hush, char *input);
int		operatorscount(char *str, int *hash);
char	*add_spaces_around_operators(char *s, int *hash);
int		typing(char *spl);
void	creat_var(t_prc **cmd);

// typedef struct s_data
// {
// 	t_env env;
// }t_data;
#endif // MINISHELL
