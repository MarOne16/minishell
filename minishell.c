/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/09 17:58:06 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// free t_list *g_all
void	feed_glob(char **argv, char **env)
{
	g_lob = (t_global *)malloc(sizeof(t_global));
	if (*env == NULL)
		env = empty_env(argv);
	g_lob->environ = env;
	g_lob->rd = 0;
	g_lob->exit_status = 0;
	g_lob->g_all = NULL;
	creat_env(env);
	creat_exp(env);
	// if (g_lob->if_free == 1)
	// {
	// 	free(env[0]);
	// 	free(env[2]);
	// 	free(env);
	// }
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

void	free_all(void)
{
	t_list	*tmp;

	while (g_lob->g_all)
	{
		tmp = g_lob->g_all;
		g_lob->g_all = g_lob->g_all->next;
		free(tmp->content);
		free(tmp);
	}
	g_lob->g_all = NULL;
}

void	free_env_exp(void)
{
	t_my_list	*tmp;

	while (g_lob->env)
	{
		tmp = g_lob->env;
		g_lob->env = g_lob->env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	while (g_lob->exp)
	{
		tmp = g_lob->exp;
		g_lob->exp = g_lob->exp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(g_lob);

}
void	close_all(t_fd *fd)
{
	t_fd	*tmp;

	while (fd)
	{
		tmp = fd;
		fd = fd->next;
		close(tmp->fd);
	}
}

void	next_cmd(t_exe **all)
{
	t_exe	*tmp;
	t_fd	*tmp2;
	char	**cmd;

	tmp = *all;
	cmd = ft_malloc(sizeof(char *) + 1);
	while (tmp)
	{
		tmp2 = tmp->fd;
		while (tmp2)
		{
			if (tmp2->fd == -1)
			{
				cmd[0] = ft_strdup_mini("");
				tmp->lakher = (void **)cmd;
				close_all(tmp->fd);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*input;
	char	*newinput;
	t_exe	*all;

	input = NULL;
	all = NULL;
	(void)argc;
	if (argc > 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		exit(1);
	}
	feed_glob(argv, env);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		input = ft_readline();
		rl_catch_signals = 0;
		if (!input || !ft_strcmp(input, "exit"))
		{
			printf("exit\n");
			break ;
		}
		newinput = replace_vars(input);
		g_lob->exit_status = 0;
		feedlist(&all, newinput);
		next_cmd(&all);
		session(all);
		free_all();
		free(input);
		all = NULL;
	}
	// free_env_exp();
	return (0);
}
