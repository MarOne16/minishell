/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/28 02:44:19 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


char	*add_spaces_around_operators(char *s, int *hash)
{
	size_t	len = ft_strlen(s);
	char	*result = malloc(3 * len + 1);
	size_t	i = 0, j = 0;

	while (i < len)
	{
		if (s[i] == '<' || s[i] == '>')
		{
			int	count = 0;
			while (i < len && (s[i] == '<' || s[i] == '>'))
			{
				count++;
				i++;
			}
			if ((count == 1 || count == 2) && hash[i] == 0)
			{
				result[j++] = ' ';
				for (int k = 0; k < count; k++)
					result[j++] = s[i - count + k];
				result[j++] = ' ';
			}
			else
				for (int k=0; k<count; ++k)
					result[j++]=s[i-count+k];
        }
        else
            result[j++]=s[i++];
    }
    result[j]='\0';
    return result;
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

void    feedlist(t_prc *all, char *input)
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
		printf("syntax error\n");
		return ;
	}
	newinput = add_spaces_around_operators(input, hash);
	allcmd = ft_split(newinput, '|', hash);
	i = -1;
	while (allcmd[++i])
	{
		for (size_t i = 0; i < ARG_MAX; i++)
			hash[i] = 0;
		feedhashtable(hash, allcmd[i]);
		cmd = ft_split(allcmd[i], ' ', hash);
		u = -1;
		while (cmd[++u])
			ft_lstadd_backcmd(&cmdspl, ft_lstnewcmd(cmd[u], typing(cmd[u])));
		ft_lstadd_backallcmd(&all, ft_lstnewallcmd(allcmd[i], cmdspl));
		cmdspl = NULL;
	}
	while (all)
	{
		printf("allcmd : %s -->  ",all->allcmd);
		while (all->cmd)
		{
			printf("[%s]->type \"%s\"\t",all->cmd->cmd, all->cmd->type);
			all->cmd = all->cmd->next;
		}
		printf("\n");
		all = all->next;
	}
	
}


int main(int ac, char **av, char **env)
{
	char *input = NULL;
	t_prc       *cmd;
	(void)ac;
	(void)av;
	(void)env;
	while ((input = readline("prompt: ")))
	{
		feedlist(cmd, input);
		cmd = NULL;
	}
	// while (cmd)
	// {
	//     printf("[%s]\n",cmd->cmd);
	//     cmd = cmd->next;
	// }
	
	return 0;
}

