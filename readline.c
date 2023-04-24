/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 15:08:02 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void	feedexe1(t_cmd *cmd, t_exe **exe)
{
	char	**lakher;
	int		i;

	while (cmd)
	{
		i = 0;
		lakher = malloc(sizeof(void *) * sizechar(cmd) + 1);
		while (cmd->type != 2)
		{
			lakher[i++] = cmd->cmd;
			cmd = cmd->next;
		}
		lakher[i] = NULL;
		ft_lstadd_backallcmd(exe, ft_lstnewallcmd((void **)lakher, NULL));
		cmd = cmd->next;
		// free(lakher);
	}
	
}

t_list *env_list()
{
	int i;
	extern char **environ;
	t_list	*all;

	i = 0;
	all = NULL;
	while (environ[i])
		ft_lstadd_back(&all,ft_lstnew(environ[i++]));
	return (all);
}



int  checkcmd(char *cmd, int *hash)
{
	int	i;
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	i = 0;
	feedhashtable(&hash, cmd);
	while (cmd[i])
	{
		if (((cmd[i] == '>' && cmd[i + 1] == '<') || \
		(cmd[i] == '<' && cmd[i + 1] == '>')) && hash[i] == 0)
			return (1);
		if (cmd[i] == '\"' && hash[i] == 0)
			dq++;
		if (cmd[i] == '\'' && hash[i] == 0)
			sq++;
		i++;
	}
	if ((dq % 2) || (sq % 2))
		return (1);
	return (0);
}

int    typing(char    *spl)
{
	if (((spl[0] == '>' && spl[1] != '<') ||(spl[0] == '<' && spl[1] != '>') || \
	(spl[0] == '>' && spl[1] == '>') || \
		((spl[0] == '<' && spl[1] == '<'))) && (ft_strlen(spl) <= 2))
		return (1);
	else if (spl[0] == '|' && ft_strlen(spl) <= 2)
		return (2);
	else
		return (0);
}

void	feedhashtable(int **hash, char *input)
{
	size_t	i;

	i = -1;
	// if (*hash)
	// {
	// 	free(*hash);
	// 	*hash = NULL;
	// }
	*hash = ft_calloc(ft_strlen(input) + 1, sizeof(int));
	while (input[++i])
	{
		if (input[i] == '\"' && input[i + 1])
			while (input[++i] != '\"' && input[i + 1])
				(*hash)[i] = 1;
		if (input[i] == '\'' && input[i + 1])
			while (input[++i] != '\'' && input[i + 1])
				(*hash)[i] = 1;
	}
}


int check_rid(t_cmd *cmdspl)
{
	t_cmd	*reset2;

	reset2 = cmdspl;

	while (reset2)
	{
		if (reset2->type == 1 && \
		(!reset2->next || (reset2->next->type != 0) || reset2->next->cmd[0] == '\t'))
			return (1);
		else if (reset2->type == 2 && (!reset2->next || (reset2->next->type == 2)))
			return (1);
		reset2 = reset2->next;
	}
	return (0);
}


void    feedlist(t_exe **all, char *input)
{
	int		u;
	int		*hash;
	char	*newinput = NULL;
	char    **cmd;
	t_cmd	*cmdspl = NULL;
	(void)all;

	hash = NULL;
	feedhashtable(&hash, input);
	newinput = add_spaces_around_operators(input, hash);
	feedhashtable(&hash, newinput);
	cmd = ft_splithash(newinput, ' ', hash);
	u = -1;
	while (cmd[++u])
		ft_lstadd_backcmd(&cmdspl, ft_lstnewcmd(cmd[u], typing(cmd[u])));
	if (checkcmd(newinput, hash) || check_rid(cmdspl) || \
	operatorscount(input, hash) == 1337)
	{
		free(hash);
		forcfree(cmdspl);
		free(newinput);
		printf(AC_RED"syntax error\n");
		return ;
	}
	table_lakher(cmdspl, all);
	creat_files(cmdspl, all);
}

void forcfree(t_cmd *input)
{
	t_cmd	*help;

	while ((input))
	{
		help = (input);
		(input)= (input)->next;
		free(help);
	}
}

char    *ft_readline()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline(AC_GREEN"Minishell> ");
    if (line)
        add_history(line);
    return (line);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int main()
{

	char *input = NULL;
	char *newinput = NULL;
	t_exe       *all = NULL;

	while ((input = ft_readline()))
	{	
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!ft_strcmp(input, "exit"))
			break;
		newinput = replace_vars(input);
		feedlist(&all, newinput);
		while (all)
		{
			int i = 0;
			while (all->lakher[i])
			{
				printf(AC_BLUE"%s \t",(char *)all->lakher[i]);
				i++;
			}
			while (all->fd)
			{
				printf(AC_BLUE"%d \t", all->fd->fd);
				all->fd = all->fd->next;
			}
			puts("");
			all = all->next;
		}
		all = NULL;
		// // forcfree(&all);
	}
	exit(0);
	return 0;
}
