/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/03/25 01:54:41 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/**
 * word = alphabets, ", ' : 0
 * --->ls | wc -l => list of words : {ls, wc, -l}
 * --->ls"$VAR kabdjcd cjhsdbvjdhsb | echo => list of words : {ls"$VAR kabdjcd cjhsdbvjdhsb | echo}
 * pipe | : 1
 * redirections : > >> < << : 2
*/
char    *typing(char    *spl)
{
	if (((spl[0] == '|') || (spl[0] == '>' && spl[1] != '<') ||
		(spl[0] == '<' && spl[1] != '>') || (spl[0] == '>' && spl[1] == '>') ||
		((spl[0] == '<' && spl[1] == '<'))) && (ft_strlen(spl) <= 2))
		return "token";
	else
		return "word";
}

// char **secendspl(char *cmd)
// {
// 	int i;
// 	char    **spl;

// 	spl = ft_split(cmd, ' ');
// 	return spl;
// }

void    feedlist(t_prc *all, char *input)
{
	int		i;
	int		u;
	char    **allcmd;
	char    **cmd;
	t_cmd	*cmdspl = NULL;

	allcmd = ft_split(input, '|');
	i = -1;
	while (allcmd[++i])
	{
		cmd = ft_split(allcmd[i], ' ');
		u = -1;
		while (cmd[++u])
			ft_lstadd_backcmd(&cmdspl, ft_lstnewcmd(cmd[u], typing(cmd[u])));
		ft_lstadd_backallcmd(&all, ft_lstnewallcmd(allcmd[i], cmdspl));
		cmdspl = NULL;
	}
	while (all)
	{
		printf("allcmd %s -->  ",all->allcmd);
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
	while ((input = readline("Enter a string: ")))
	{
		cmd = NULL;
		feedlist(cmd, input);
	}
	// while (cmd)
	// {
	//     printf("[%s]\n",cmd->cmd);
	//     cmd = cmd->next;
	// }
	
	return 0;
}

