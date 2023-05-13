/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:04:01 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/13 16:40:43 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkcmd(char *cmd, int *hash)
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

int	typing(char *spl)
{
	if (((spl[0] == '>' && spl[1] != '<') \
		|| (spl[0] == '<' && spl[1] != '>') \
		|| (spl[0] == '>' && spl[1] == '>') \
		|| (spl[0] == '<' && spl[1] == '<')))
		return (free(spl), 1);
	else if (spl[0] == '|' && ft_strlen(spl) <= 2)
		return (free(spl), 2);
	else
		return (free(spl), 0);
}

void	feedhashtable(int **hash, char *input)
{
	size_t	i;
	int		*hash2;

	hash2 = ft_malloc(sizeof(int) * (ft_strlen(input) + 1), 0);
	i = -1;
	*hash = hash2;
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

void	feedlist(t_exe **all, char *input)
{
	int		u;
	int		*hash;
	char	*newinput;
	char	**cmd;
	t_cmd	*cmdspl;

	hash = NULL;
	cmdspl = NULL;
	newinput = add_spaces_around_operators(input, hash);
	feedhashtable(&hash, newinput);
	cmd = ft_splithash(newinput, ' ', hash);
	u = -1;
	while (cmd[++u])
		ft_lstadd_backcmd(&cmdspl, \
		ft_lstnewcmd(removequote(cmd[u]), typing(cmd[u])));
	free(cmd);
	if (checkcmd(newinput, hash) || check_rid(cmdspl) || \
	operatorscount(input, hash) == 1337)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `\n", 2);
		g_lob->exit_status = 258;
		return ;
	}
	table_lakher(cmdspl, all);
	if (cmdspl && cmdspl->next && all && *all)
		creat_files(cmdspl, all);
}
