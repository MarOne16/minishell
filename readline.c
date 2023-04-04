/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/04 04:04:21 by mqaos            ###   ########.fr       */
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
    char    *result = malloc(strlen(s) + (operatorscount(s, hash) * 2) + 1);
    int i;
    int u;
    int j = 0;
    int c;

    i = 0;
    while (s[i])
    {
        u = i;
        c = 0;
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
        else if(c > 0)
        {
            while (c)
            {
                result[j++] = s[i++];
                c--;
            }
        }
        result[j++] = s[i];
        i++;
    }
    result[j]='\0';
    return (result);
}

int checkcmd(char *cmd, int *hash)
{
	int i = 0;
	int dq;
	int sq;
	
	dq = 0;
	sq = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' && hash[i] == 0)
			dq++;
		if (cmd[i] == '\'' && hash[i] == 0)
			sq++;
		i++;
	}
	if (dq % 2)
		return(1);
	if (sq % 2)
		return(1);
	return(0);
	
}


char    *typing(char    *spl)
{
	if (((spl[0] == '>' && spl[1] != '<') || spl[0] == '='||
		(spl[0] == '<' && spl[1] != '>') || (spl[0] == '>' && spl[1] == '>') ||
		((spl[0] == '<' && spl[1] == '<'))) && (ft_strlen(spl) <= 2))
		return "token";
	else
		return "word";
}


void	feedhashtable(int *hush, char *input)
{
	size_t i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"')
		{
			while (input[++i] != '\"' && input[i])
				hush[i] = 1;
		}
		if(input[i] == '\'')
		{
			while (input[++i] != '\'' && input[i])
				hush[i] = 1;
		}
	}
	
}

void    feedlist(t_prc **all, char *input)
{
	int		i;
	int		u;
	int		hash[ARG_MAX] = {0};
	char	*newinput;
	char    **allcmd;
	char    **cmd;
	t_cmd	*cmdspl = NULL;


	feedhashtable(hash, input);
	if (checkcmd(input, hash))
	{
		printf(AC_RED"syntax error\n");
		return ;
	}
	newinput = add_spaces_around_operators(input, hash);
	allcmd = ft_splithash(newinput, '|', hash);
	i = -1;
	while (allcmd[++i])
	{
		for (size_t i = 0; i < ARG_MAX; i++)
			hash[i] = 0;
		feedhashtable(hash, allcmd[i]);
		cmd = ft_splithash(allcmd[i], ' ', hash);
		u = -1;
		while (cmd[++u])
			ft_lstadd_backcmd(&cmdspl, ft_lstnewcmd(cmd[u], typing(cmd[u])));
		ft_lstadd_backallcmd(all, ft_lstnewallcmd(allcmd[i], cmdspl));
		cmdspl = NULL;
	}
	while ((*all))
	{
		printf(AC_YELLOW"\ncmd : %s -->  ",(*all)->allcmd);
		while ((*all)->cmd)
		{
			printf(AC_CYAN"[%s]->type \"%s\"\t",(*all)->cmd->cmd, (*all)->cmd->type);
			(*all)->cmd = (*all)->cmd->next;
		}
		printf("\n");
		(*all) = (*all)->next;
	}
}
void forcfree(t_prc *input)
{
	t_prc	*help;
	t_cmd	*help2;

	while (input)
	{
		while (input->cmd)
		{
			help2 = input->cmd;
			input->cmd = input->cmd->next;
			free(help2);
		}
		help = input;
		input = input->next;
		free(help);
	}
}

int main(int ac, char **av)
{
	char *input = NULL;
	t_prc       *all = NULL;
	(void)ac;
	(void)av;
	while ((input = replace_env_vars(readline("prompt: "))))
	{
		feedlist(&all, input);
		forcfree(all);
	}

	return 0;
}

