/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:37:03 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/28 17:27:20 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINISHELL)
#define MINISHELL
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

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

// list tools
t_prc	*ft_lstnewallcmd(char *allcmd, t_cmd *cmd);
t_cmd	*ft_lstnewcmd(char *cmd, char *type);
void	ft_lstadd_front(t_prc **lst, t_prc *new);
t_prc	*ft_lstlastallcmd(t_prc *lst);
t_cmd	*ft_lstlastcmd(t_cmd *lst);
void	ft_lstadd_backallcmd(t_prc **lst, t_prc *new);
void	ft_lstadd_backcmd(t_cmd **lst, t_cmd *new);
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

// readline
void    feedlist(t_prc **all, char *input);
void	feedhashtable(int *hush, char *input);
char	*add_spaces_around_operators(char *s, int *hash);
char	*typing(char *spl);

// typedef struct s_env
// {
	
// }t_env;
// typedef struct s_data
// {
// 	t_env env;
// }t_data;
#endif // MINISHELL
