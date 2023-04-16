/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/16 02:57:24 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
			if (reset2->type != 0 && (!reset2->next || (reset2->next->type == reset2->type)))
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
	t_cmd	*cmdspl = NULL;

	hash = NULL;
	feedhashtable(&hash, input);
	newinput = add_spaces_around_operators(input, hash);
	feedhashtable(&hash, newinput);
	cmd = ft_splithash(newinput, ' ', hash);
	u = -1;
	while (cmd[++u])
		ft_lstadd_backcmd(&cmdspl, ft_lstnewcmd(cmd[u], typing(cmd[u])));
	ft_lstadd_backallcmd(all, ft_lstnewallcmd(newinput, cmdspl));
	if (checkcmd(newinput, hash) || check_rid(all) || \
	operatorscount(input, hash) == 1337)
	{
		free(hash);
		forcfree(all);
		free(newinput);
		printf(AC_RED"syntax error\n");
		return ;
	}
	u = -1;
	while (cmd[++u])
		printf(AC_RED"%s\n",removequote(cmd[u]));
	// creat_var(all);
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
			// input = replace_env_vars(input);
			newinput = replace_vars(input);
			feedlist(&all, newinput);
			all = NULL;
			// forcfree(&all);
		}
	}
	exit(0);
	return 0;
}

