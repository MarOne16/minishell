/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousouf <mbousouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:56:50 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/18 01:32:43 by mbousouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* replace_env_vars(char* string) {
    char* new_string = calloc(strlen(string) + 1, 1);
    char* out = new_string;
    size_t str_len = strlen(string);
    size_t i = 0;

    while (i < str_len) {
        if (string[i] == '$') {
            char* var_start = &string[i] + 1;
            size_t var_len = 0;

            while (isalnum(string[i + 1 + var_len]) || string[i + 1 + var_len] == '_') {
                var_len++;
            }

            char var_name[var_len + 1];
            memcpy(var_name, var_start, var_len);
            var_name[var_len] = '\0';

            char* var_value = getenv(var_name);
            if (var_value) {
                size_t val_len = strlen(var_value);
                new_string = realloc(new_string, out - new_string + val_len + 3);
                if (!new_string) {
                    fprintf(stderr, "Error: Failed to allocate memory.\n");
                    exit(EXIT_FAILURE);
                }
                *out++ = '\'';
                for (size_t j = 0; j < val_len; j++) {
                    *out++ = var_value[j];
                }
                *out++ = '\'';
                i += var_len + 1;
                continue;
            }
        }

        *out++ = string[i++];
    }

    *out = '\0';
    return new_string;
}


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

char	*getvariable(char *input)
{
	char *need = malloc(sizeof(char) * getsize(input) + 1);
	int	i = 0;
	int	j = 0;
    while (input[i])
    {
        if (input[i] == '$')
        {
            while (input[i + 1] == '$')
                i++;
            j = 0;
            i++;
            while (input[i] != 32 && input[i])
            {
                need[j] = input[i];
                i++;
                j++;
                if (input[i] == '$')
                    return(need);
            }
            return(need);
        }
        i++;
    }
	return (input);
}

int getsize(char *str)
{
    int i = 0;
    int j;
    while (str[i])
    {
        if (str[i] == '$')
        {
            while (str[i + 1] == '$')
                i++;
            j = 0;
            i++;
            while (str[i] != 32 && str[i] && str[i] != '$')
            {
                j++;
                i++;
                if (str[i] == '$')
                    return (j);
            }
            return (j);
        }
        i++;
    }
    return(0);
}

char *remplace(char *old, char **env)
{
	int		i;
	char	*variable;

	i = -1;
	while (env[++i])
	{
		if (strstr(env[i],getvariable(old)))
		{
			variable = malloc(ft_strlen(env[i]) + 1);
			variable = env[i];
			variable[ft_strlen(env[i])] = 0;
			return(variable);
		}
		if (env[i + 1] == 0)
			return(old);
		
	}
	return (old);
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
	char	*newinput = NULL;
	char    **allcmd;
	char    **cmd;
	t_cmd	*cmdspl = NULL;


	// printf(AC_BLACK"\n%s\n",input);
	feedhashtable(hash, input);
	// if (checkcmd(input, hash))
	// {
	// 	printf(AC_RED"syntax error\n");
	// 	return ;
	// }
	// for (size_t i = 0; i < ft_strlen(input); i++)
		// printf("%d",hash[i]);
	newinput = add_spaces_around_operators(input, hash);
	// printf(AC_RED"\n%s\n",newinput);
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
		ft_lstadd_backallcmd(all, ft_lstnewallcmd(allcmd[i], cmdspl));
		cmdspl = NULL;
	}
	// while ((*all))
	// {
	// 	printf(AC_YELLOW"\ncmd : %s -->  ",(*all)->allcmd);
	// 	while ((*all)->cmd)
	// 	{
	// 		printf(AC_CYAN"[%s]->type \"%s\"\t",(*all)->cmd->cmd, (*all)->cmd->type);
	// 		(*all)->cmd = (*all)->cmd->next;
	// 	}
	// 	printf("\n");
	// 	(*all) = (*all)->next;
	// }
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
void iter(int i)
{
    t_list *temp;
    if( i == 1)
	temp = (*glob->env);
    else
    temp = (*glob->exp);
    if(temp == NULL)
        return;
	while (temp != NULL)
	{
		printf("%s || %s\n", (temp)->name, (temp)->value);
		temp = (temp)->next;
	}
}
int main(int ac, char **av,char ** env)
{
	char *input = NULL;
	t_prc       *all = NULL;
    glob = (t_global *)malloc(sizeof(t_global));
	(void)ac;
    if(*env == NULL)
    {
        env = empty_env(av);
    }
    Creat_env(env);
    Creat_exp(env);
	while ((input = readline("mini-1.0$ ")))
	{
        if (!input)
            return(1);
        add_history(input);
		feedlist(&all, input);
        session(&all);
        all = NULL;
		forcfree(all);
        
	}
    
	return 0;
}

