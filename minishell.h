/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:37:03 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/24 23:21:58 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINISHELL)
#define MINISHELL
# include <unistd.h>
# include <stdio.h>
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
size_t	ft_strlen(const char *s);
int		nb_c(char const *s, char c);
int		strlenword(char const *s, char c, int i);
void	ft_free(char **strs, int j);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// readline
void    feedlist(t_prc *cmd, char *input);
char	*typing(char *spl);


#endif // MINISHELL
