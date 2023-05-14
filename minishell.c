/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/14 18:15:34 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	feed_glob(char **argv, char **env)
{
	g_lob = (t_global *)malloc(sizeof(t_global));
	g_lob->g_exp = NULL;
	g_lob->g_all = NULL;
	if (*env == NULL)
		env = empty_env(argv, env);
	g_lob->environ = env;
	g_lob->rd = 0;
	g_lob->exit_status = 0;
	creat_env(env);
	creat_exp(env);
}

// sort list of env
void	sort_exp_l(t_my_list **exp)
{
	t_my_list	*tmp;
	t_my_list	*tmp2;
	char		*name;
	char		*value;

	tmp = *exp;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				name = tmp->name;
				value = tmp->value;
				tmp->name = tmp2->name;
				tmp->value = tmp2->value;
				tmp2->name = name;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	free_all(char *input, t_exe **all)
{
	t_list	*tmp;

	while (g_lob->g_all)
	{
		tmp = g_lob->g_all;
		g_lob->g_all = g_lob->g_all->next;
		free(tmp->content);
		free(tmp);
	}
	free(input);
	*all = NULL;
	g_lob->g_all = NULL;
}

void	free_env_exp(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

int	main(int argc, char *argv[], char **env)
{
	char	*input;
	char	*newinput;
	t_exe	*all;

	input = NULL;
	all = NULL;
	if (argc > 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		exit(1);
	}
	feed_glob(argv, env);
	while (1)
	{
		input = ft_readline("minishell> ");
		if (!input || !ft_strcmp(input, "exit"))
			break ;
		newinput = replace_vars(input);
		feedlist(&all, newinput);
		next_cmd(&all);
		session(all);
		sort_exp_l(&g_lob->exp);
		free_all(input, &all);
	}
	free_env_exp();
}
