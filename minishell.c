/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/08 10:44:29 by mbousouf         ###   ########.fr       */
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

void	free_env_exp()
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
	char 	**cmd;

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
		if (!input)
			break ;
		if (!ft_strcmp(input, "exit"))
			break ;
		newinput = replace_vars(input);
		g_lob->exit_status = 0;
		feedlist(&all, newinput);
		next_cmd(&all);
		session(all);
		all = NULL;
		free_all();
		free(input);
	}
	free_env_exp();
	return (0);
}
// TODO :: echo hi >         ./outfiles/outfile01 bye :: cat <file_not_ fond | cat < file_found :: export GHOST=123 | env | grep GHOST
// int main(int argc, char *argv[], char **env)
// {
// 	(void)argv;
// 	(void)argc;
// 	char *input = NULL;
// 	char *newinput = NULL;
// 	t_exe       *all = NULL;
// 	g_lob = (t_global *)malloc(sizeof(t_g_lobal));
// 	if( *env == NULL)
// 	{
// 		env = empty_env(argv);
// 	}
// 	creat_env(env);
// 	creat_exp(env);
// 	while ((input = ft_readline()))
// 	{	
// 		signal(SIGINT, sig_handler);
// 		signal(SIGQUIT, SIG_IGN);
// 		if (!ft_strcmp(input, "exit"))
// 			break;
// 		newinput = replace_vars(input);
// 		feedlist(&all, newinput);
// 		all = NULL;
// 		// // forcfree(&all);
// 	}
// 	exit(0);
// 	return 0;
// }