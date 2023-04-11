/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/11 00:52:28 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int operatorscount(char *str, int *hash)
{
	int i;
	int count = 0;
	int c = 0;

	i = -1;
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
	}
	return (c);
}

char    *add_spaces_around_operators(char *s, int *hash)
{
	char    *result = malloc(ft_strlen(s) + (operatorscount(s, hash) * 2) + 1);
	int i;
	int u;
	int j = 0;
	int c;

	i = 0;
	while (s[i])
	{
		u = i;
		c = 0;
		if (s[i] == '|' && hash[i] == 0)
		{
			result[j++] = ' '; 
				result[j++] = s[i++];
			result[j++] = ' ';
		}
		while(s[u] && (s[u] == '<' || s[u] == '>') && hash[u] == 0 )
		{
			c++;
			u++;
		}
		if (c == 1 || c == 2)
		{
			result[j++] = ' '; 
			while (c)
			{
				result[j++] = s[i++];
				c--;
			}
			result[j++] = ' ';
		}
		else if(c > 2)
		{
			while (c)
			{
				result[j++] = s[i++];
				c--;
			}
		}
		else
			result[j++] = s[i++];
	}
	result[j]='\0';
	return (result);
}

int  checkcmd(char *cmd, int *hash)
{
	int i = 0;
	int dq;
	int sq;
	
	dq = 0;
	sq = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '<') || 
		((cmd[i] == '<' && cmd[i + 1] == '>') && hash[i] == 0))
			return(1);
		if (cmd[i] == '\"' && hash[i] == 0)
			dq++;
		if (cmd[i] == '\'' && hash[i] == 0)
			sq++;
		i++;
	}
	if ((dq % 2) || (sq % 2))
		return(1);
	return(0);
}

int    typing(char    *spl)
{
	if (((spl[0] == '>' && spl[1] != '<') || spl[0] == '='|| spl[0] == '|' || 
		(spl[0] == '<' && spl[1] != '>') || (spl[0] == '>' && spl[1] == '>') ||
		((spl[0] == '<' && spl[1] == '<'))) && (ft_strlen(spl) <= 2))
		return (1);
	else
		return (0);
}

void	feedhashtable(int **hash, char *input)
{
	size_t	i;

	i = -1;
	if (*hash || hash)
	{
		free(*hash);
		*hash = NULL;
	}
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


int check_rid(t_prc **all)
{
	t_prc	*reset;
	t_cmd	*reset2;

	reset = *all;
	while (reset && all && (*all))
	{
		reset2 = reset->cmd;
		while (reset2)
		{
			if (reset2->type == 1 && (!reset2->next || reset2->next->type == 1))
				return (1);
			reset2 = reset2->next;
		}
		reset = reset->next;
	}
	return (0);
}

char **feedchardouble(t_prc **all)
{
	char	**spl;
	int		i;
	t_cmd	*rest3;

	spl = (char **)malloc((sizeof(char *) * 1) + 1);
	i = 0;
	rest3 = (*all)->cmd;
	while (rest3)
	{
		spl[i++] = removequote(rest3->cmd);
		// spl[i++] = rest3->cmd;
		rest3 = rest3->next;
	}
	return (spl[i] = 0, spl);
}

void    feedlist(t_prc **all, char *input)
{
	int		u;
	int		*hash;
	char	*newinput = NULL;
	char    **cmd;
	char    **cmdfinal = NULL;
	t_cmd	*cmdspl = NULL;

	hash = NULL;
	feedhashtable(&hash, input);
	newinput = add_spaces_around_operators(input, hash);
	feedhashtable(&hash, newinput);
	cmd = ft_splithash(newinput, ' ', hash);
	u = -1;
	while (cmd[++u])
	{
		ft_lstadd_backcmd(&cmdspl, ft_lstnewcmd(cmd[u], typing(cmd[u])));
	}
	ft_lstadd_backallcmd(all, ft_lstnewallcmd(newinput, cmdspl));
	cmdspl = NULL;
	if (checkcmd(newinput, hash) || check_rid(all))
	{
		free(hash);
		forcfree(all);
		free(newinput);
		printf(AC_RED"syntax error\n");
		return ;
	}
	cmdfinal = feedchardouble(all);
	u = -1;
	while (cmdfinal[++u])
		printf(AC_RED"%s\n",cmdfinal[u]);
}

void forcfree(t_prc **input)
{
	t_prc	*help;
	t_cmd	*help2;

	while (*input)
	{
		while ((*input)->cmd)
		{
			help2 = (*input)->cmd;
			(*input)->cmd = (*input)->cmd->next;
			free(help2);
		}
		help = (*input);
		(*input) = (*input)->next;
		free(help);
	}
}

int main(int argc, char *argv[], char **env)
{
	(void)argv;
	(void)argc;
	environ = env;
	char *input = NULL;
	char *newinput = NULL;
	t_prc       *all = NULL;

	while ((input = readline(AC_GREEN"prompt: ")))
	{
		if (input)
		{
			newinput = replace_env_vars(input);
			add_history(input);
			feedlist(&all, newinput);
			all = NULL;
			// forcfree(&all);
		}
	}
	exit(0);
	return 0;
}

