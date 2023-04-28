/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:13:17 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/28 16:14:02 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// free t_list *g_all
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

int	main(int argc, char *argv[], char **env)
{
	char	*input;
	char	*newinput;
	t_exe	*all;
	// int		i;

	input = NULL;
	all = NULL;
	(void)argc;
	(void)argv;
	glob = (t_global *)malloc(sizeof(t_global));
	if(*env == NULL)
		env = empty_env(argv);
	glob->rd = 0;
	glob->g_all = NULL;
	Creat_env(env);
	Creat_exp(env);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		rl_catch_signals = 0;
		input = ft_readline();
		if (!input)
			break ;
		if (!ft_strcmp(input, "exit"))
			break ;
		newinput = replace_vars(input);
		feedlist(&all, newinput);
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