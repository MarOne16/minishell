/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/24 15:37:52 by mbousouf         ###   ########.fr       */
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

int operatorscount(char *str, int *hash)
{
	int i;
	int count = 0;
	int c = 0;

	i = -1;
	feedhashtable(&hash, str);
	while (str[++i])
	{
			count = 0;
			while (str[i] && (str[i] == '<' || str[i] == '>') && hash[i] == 0)
			{
				count++;
				i++;
			}
			if ((count == 1 || count == 2))
				c++;
			else if (count > 2)
				return (1337);
	}
	return (c);
}

char    *add_spaces_around_operators(char *s, int *hash)
{
	char    *result;
	int i;
	int u;
	int c;

	i = 0;
	
	result = ft_strdup("");
	feedhashtable(&hash, s);
	while (s[i])
	{
		u = i - 1;
		c = 0;
		if (s[i] == '|' && hash[i] == 0)
		{
			result = ft_strjoin_char(result,' ');
			result = ft_strjoin_char(result, s[i++]);
			result = ft_strjoin_char(result,' ');
		}
		else
		{
			while(s[++u] && (s[u] == '<' || s[u] == '>') && hash[u] == 0)
				c++;
			if (c == 1 || c == 2)
			{
				result = ft_strjoin_char(result,' ');
				while (s[i] && (s[i] == '>' || s[i] == '<'))
					result = ft_strjoin_char(result, s[i++]);
				result = ft_strjoin_char(result,' ');
			}
			else if(c > 2)
				while (s[i] && c--)
					result = ft_strjoin_char(result, s[i++]);
			else
				result = ft_strjoin_char(result, s[i++]);
		}
	}
	return (result);
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
void iter(int n)
{
	t_my_list * tmp;
	if(n == 1)
	{
		tmp = (glob->env);
		while(tmp)
		{
			printf("%s%s\n",tmp->name,tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		tmp = (glob->exp);
		while(tmp)
		{
			printf("%s%s\n",tmp->name,tmp->value);
			tmp = tmp->next;
		}
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

int main(int argc, char *argv[], char **env)
{
	(void)argv;
	(void)argc;
	char *input = NULL;
	char *newinput = NULL;
	t_exe       *all = NULL;
	glob = (t_global *)malloc(sizeof(t_global));
	if( *env == NULL)
	{
		env = empty_env(argv);
	}
	Creat_env(env);
	Creat_exp(env);
	while ((input = ft_readline()))
	{	
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!ft_strcmp(input, "exit"))
			break;
		newinput = replace_vars(input);
		feedlist(&all, newinput);
		session(all);
		all = NULL;
		// // forcfree(&all);
	}
	exit(0);
	return 0;
}
