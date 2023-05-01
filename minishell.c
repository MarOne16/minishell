/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/05/01 16:59:44 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// free t_list *g_all
void	feed_glob(char **argv, char **env)
{
	glob = (t_global *)malloc(sizeof(t_global));
	if (*env == NULL)
		env = empty_env(argv);
	glob->rd = 0;
	glob->exit_status = 0;
	glob->g_all = NULL;
	Creat_env(env);
	Creat_exp(env);
}

void	free_all(void)
{
	t_list	*tmp;

	while (glob->g_all)
	{
		tmp = glob->g_all;
		glob->g_all = glob->g_all->next;
		free(tmp->content);
		free(tmp);
	}
	glob->g_all = NULL;
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
			if(tmp2->fd == -1)
			{
				cmd[0] = ft_strdup_mini("");
				tmp->lakher = (void**)cmd;
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
		glob->exit_status = 0;
		feedlist(&all, newinput);
		next_cmd(&all);
		session(all);
		all = NULL;
		free(input);
	}
	free_all();
	exit(0);
	return (0);
}

// int main(int argc, char *argv[], char **env)
// {
// 	(void)argv;
// 	(void)argc;
// 	char *input = NULL;
// 	char *newinput = NULL;
// 	t_exe       *all = NULL;
// 	glob = (t_global *)malloc(sizeof(t_global));
// 	if( *env == NULL)
// 	{
// 		env = empty_env(argv);
// 	}
// 	Creat_env(env);
// 	Creat_exp(env);
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