# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
	#include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

// char	*ft_strjoin_char(char *s, char c)
// {
// 	size_t	len;
// 	char	*str;
// 	int		i;

// 	if (!s)
// 		return (NULL);
// 	len = ft_strlen(s) + 1;
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = c;
// 	str[i + 1] = '\0';
//     free(s);
// 	return (str);
// }
// char* replace(char *str, char *from, char *to)
// {
//     char *newinput = malloc(strlen(str) + (strlen(to) - strlen(from)) + 10);
//     int i = 0;
//     int j;
//     int off = 0;
//     int z;
//     int u  = 0;
//     while (str[i])
//     {
//         if (str[i] == '$')
//         {
//             while (str[i + 1] == '$')
//             {
//                 newinput[i] = str[i];
//                 i++;
//             }
//             j = 0;
//             z = i;
//             while (str[i] != 32 && str[i] && str[i] != '$')
//             {
//                 j++;
//                 i++;
//                 // if (str[i] == '$')
//                 //     break;
//             }
//             while (to[u])
//             {
//                 while (to[u] != '=' && off == 0)
//                 {
//                     if (to[u + 1] == '=')
//                         off = 1;
//                     u++;
//                 }
//                 newinput[z] = to[u];
//                 u++;
//                 z++;
//             }
//             while (str[i])
//             {
//                 newinput[z] = str[i];
//                 i++;
//             }
//             newinput[z] = 0;
//             return(newinput);
//         }
//         else
//             newinput[i] = str[i];
//         i++;
//     }
//     newinput[i] = 0;
//     printf("\n%s\n",newinput);
//     return(newinput);

// }

// int getsize(char *str)
// {
//     int i = 0;
//     int j;
//     while (str[i])
//     {
//         if (str[i] == '$')
//         {
//             while (str[i + 1] == '$')
//                 i++;
//             j = 0;
//             i++;
//             while (str[i] != 32 && str[i] && str[i] != '$')
//             {
//                 j++;
//                 i++;
//                 if (str[i] == '$')
//                     return (j);
//             }
//             return (j);
//         }
//         i++;
//     }
//     return(0);
// }

// void    ft_readline(char **env, char *input)
// {
//     int i = 0;
//     int j;
//     char *newinput = 0;
//     char *need = malloc(sizeof(char) * getsize(input) + 1);
//     while (input[i])
//     {
//         if (input[i] == '$')
//         {
//             while (input[i + 1] == '$')
//                 i++;
//             j = 0;
//             i++;
//             while (input[i] != 32 && input[i])
//             {
//                 need[j] = input[i];
//                 i++;
//                 j++;
//                 if (input[i] == '$')
//                     break;
//             }
//             break;
//         }
//         i++;
//     }
//     i = 0;
//     while (env[i])
//     {
//         if (strstr(env[i],need) != NULL)
//         {
//             newinput = replace(input,need,env[i]);
//             printf("\n%s\n",newinput);
//         }
//         i++;
//     }
		
// }

// int main(int argc, char const *argv[], char **env)
// {
		
//     // (void)argv;
//     // (void)argc;
//     // char *input = NULL;
//     // int i = 0;
//     // while ((input = readline("prompt : ")))
//     // {
//     //     ft_readline(env,input);
//     // }
//     char str[] = "echo | hello mar";
//     char need[] = "hello";
//     printf("%s\n",strstr(str,need));
//     printf("%s",need); 
//     return 0;
// }


// #include <stdlib.h>
// #include <string.h>


// char* replace_env_vars(char* string)
// {
//     char* new_string = malloc(strlen(string) + 1);
//     char* out = new_string;
//     size_t str_len = strlen(string);
//     size_t i = 0;
//     while (i < str_len) {
//         if (string[i] == '$') {
//             char* var_start = &string[i] + 1;
//             size_t var_len = 0;
//             while (isalnum(string[i + 1 + var_len]) || string[i + 1 + var_len] == '_') {
//                 var_len++;
//             }
//             char var_name[var_len + 1];
//             strncpy(var_name, var_start, var_len);
//             var_name[var_len] = '\0';
//             char* var_value = getenv(var_name);
//             if (var_value) {
//                 size_t val_len = strlen(var_value);
//                 strncpy(out, var_value, val_len);
//                 out += val_len;
//                 i += var_len + 1;
//                 continue;
//             }
//         }
//         *out++ = string[i++];
//     }
//     *out = '\0';
//     return new_string;
// }

// int main(int argc, char const *argv[])
// {
//     char input_string[] = "The current path is $$PATH\" and the home directory is $HOE.";
//     char* output_string = replace_env_vars(input_string);
//     printf("%s\n", output_string);
//     free(output_string);

//     return 0;
// }
// int main() {
//     char* path = getenv("path");
//     if (path != NULL) {
//         printf("The PATH variable is set to: %s\n", path);
//     } else {
//         printf("The PATH variable is not set.\n");
//     }
//     return 0;
// }
#include <stdlib.h>

// int operatorscount(char *str, int *hash)
// {
//     int i;
//     int count = 0;
//     int c = 0;

//     i = -1;
//     while (str[++i])
//     {
//             count = 0;
//             while (str[i] && (str[i] == '<' || str[i] == '>') && hash[i] == 0)
//             {
//                 count++;
//                 i++;
//             }
//             if ((count == 1 || count == 2))
//                 c++;
//     }
//     return (c);
// }

// char    *add_spaces_around_operators(char *s, int *hash)
// {
//     char    *result = malloc(strlen(s) + (operatorscount(s, hash) * 2) + 1);
//     int i;
//     int u;
//     int j = 0;
//     int c;

//     i = 0;
//     while (s[i])
//     {
//         u = i;
//         c = 0;
//         while(s[u] && (s[u] == '<' || s[u] == '>') && hash[u] == 0 )
//         {
//             c++;
//             u++;
//         }
//         if (c == 1 || c == 2)
//         {
//             result[j++] = ' '; 
//             while (c)
//             {
//                 result[j++] = s[i++];
//                 c--;
//             }
//             result[j++] = ' ';
//         }
//         else if(c > 0)
//         {
//             while (c)
//             {
//                 result[j++] = s[i++];
//                 c--;
//             }
//         }
//         result[j++] = s[i];
//         i++;
//     }
//     result[j]='\0';
//     return (result);
// }

// int getsize(char *str)
// {
// 		int i = 0;
// 		int j;
// 		while (str[i])
// 		{
// 				if (str[i] == '$')
// 				{
// 						while (str[i + 1] == '$')
// 								i++;
// 						j = 0;
// 						i++;
// 						while (str[i] != 32 && str[i] && str[i] != '$')
// 						{
// 								j++;
// 								i++;
// 								if (str[i] == '$')
// 										return (j);
// 						}
// 						return (j);
// 				}
// 				i++;
// 		}
// 		return(0);
// }

// char	*getvariable(char *input, int *hash)
// {
// 	char *need = malloc(sizeof(char) * getsize(input) + 1);
// 	int	i = 0;
// 	int	j = 0;
// 		while (input[i])
// 		{
// 				if (input[i] == '$')
// 				{
// 						while (input[i + 1] == '$')
// 								i++;
// 						j = 0;
// 						hash[i] = 1;
// 						i++;
// 						while (input[i] != 32 && input[i])
// 						{
// 								need[j] = input[i];
// 								hash[i] = 1;
// 								i++;
// 								j++;
// 								if (input[i] == '$')
// 										return(need);
// 						}
// 						return(need);
// 				}
// 				i++;
// 		}
// 	return (input);
// }

// char* replace_env_vars(char* string)
// {
// 	int i = 0;
// 	int j = 0;
// 	int u = 0;
// 	char *newcmd = NULL;

// 	while (string[i])
// 	{
// 		if (string[i] == '$')
// 		{
// 			j++;
// 			while (string[++i] != '$' && string[i] != 32)
// 				j++;
// 		}
// 		else
// 		{
// 			while (string[i] != '$' && string[i])
// 				i++;
// 		}
// 		newcmd = ft_strjoin(newcmd,ft_substr(string,u + j,i));
// 		printf("\n[%s]\n",ft_substr(string,u + j,i));
// 		u = i;
// 	}
// 	return(newcmd);
// }

// #include <stdlib.h>
// #include <unistd.h>
// #include <stdio.h>


// #include <stdlib.h>




// int main() {
// 	char str[] = "echo $PATH and$USER";
// // 	int *hash = calloc(ft_strlen(str),4);
// //   char *strr = replace_env_vars(str);
//   printf("%s",replace_env_vars(str));
// // for (size_t i = 0; i < strlen(str); i++)
// // {
// // 	printf("%d",hash[i]);
// // }

// 	return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// char* add_space_before_double_quote(char* str) {
//     char* new_str = malloc(strlen(str) * 2 + 1);
    
//     int i = 0, j = 0;
//     while (str[i] != '\0') {
//         if (str[i] == '"') {
//             new_str[j++] = ' '; 
//         }
//         new_str[j++] = str[i++]; 
//     }
//     new_str[j] = '\0';
    
//     return new_str;
// }


// int main(int argc, char **argv) {
//     if (check_pip(argv[1]))
//         puts("error");
//     else
//         puts("good");
//     return 0;
// }

// char *removequote(char *str)
// {
//     char *newstr;
//     int  i;

//     i = 0;
//     newstr = ft_strdup("");
//     while (str[i])
//     {
//         if (str[i] == '\"' || str[i] == '\'')
//             i++;
//         else
//         {
//             newstr = ft_strjoin_char(newstr , str[i]);
//             i++;
//         }
//     }
//     return(newstr);
// }
// int main()
// {
//     char *newstr;
//     char str[] = "hello\"maro";
//     newstr = removequote(str);
//     while (1)
//     {
//         /* code */
//     }
    
//     return 0;
// }
// #include <stdlib.h> // for malloc and free functions

char	*ft_strjoin_char(char *s, char c)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

static char *ft_strjoinn(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return NULL;

    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);

    char *result = malloc(len_s1 + len_s2 + 1);

    if (result == NULL)
        return NULL;

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
size_t	ft_strlenn(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		u;
	char	*s3;

	i = -1;
	u = -1;
	s3 = malloc(ft_strlenn(s1) + ft_strlenn(s2) + 1);
	if (!s3)
		return (0);
	while (s1 && s1[++i])
		s3[++u] = s1[i];
	i = -1;
	while (s2[++i] && s2)
	{
		s3[++u] = s2[i];
		if (s3[u] == '\n')
			break ;
	}
	s3[++u] = '\0';
	free(s1);
	return (s3);
}

int	removeline(char *str)
{
	int	start;
	int	sar;
	int	x;

	start = 0;
	sar = 0;
	x = 0;
	while (str[start])
	{
		if (x)
			str[sar++] = str[start];
		if (str[start] == '\n')
			x = 1;
		str[start] = '\0';
		start++;
	}
	return (x);
}

char	*get_next_line(int fd)
{
	static char	buffmax[2147483647];
	char		*buff;

	buff = NULL;
	while (buffmax[0] || read(fd, buffmax, 3) > 0)
	{
		buff = ft_join(buff, buffmax);
		if (removeline(buffmax))
			break ;
		if (read(fd, buffmax, 0) < 0)
			return (free(buff), NULL);
	}
	return (buff);
}
char    *add_spaces_around_operators(char *s)
{
	char    *result;
	int i;
	int u;
	int j = 0;
	int c;

	i = 0;
	result = ft_strdup("");
	while (s[i])
	{
		u = i - 1;
		c = 0;
		if (s[i] == '|')
		{
			result = ft_strjoin_char(result,' ');
			result = ft_strjoin_char(result, s[i++]);
			result = ft_strjoin_char(result,' ');
		}
		while(s[++u] && (s[u] == '<' || s[u] == '>') )
			c++;
		if (c == 1 || c == 2)
		{
			result = ft_strjoin_char(result,' ');
			while (s[i] && (s[i] == '>' || s[i] == '<'))
				result = ft_strjoin_char(result, s[i++]);
			result = ft_strjoin_char(result,' ');
		}
		else if(c > 2)
			while (s[i] && c--)
				result = ft_strjoin_char(result, s[i++]);
		else
			result = ft_strjoin_char(result, s[i++]);
	}
	return (result);
}

t_list *env_list()
{
	int i;
	extern char **environ;
	t_list	*all;

	i = 0;
	all = NULL;
	while (environ[i])
		ft_lstadd_back(&all,ft_lstnew(environ[i++]));
	return (all);
}

// char	*get_env_value(char *name)
// {
// 	int		i;
// 	extern char **environ;
// 	size_t	len;

// 	len = ft_strlen(name);
// 	i = 0;
// 	while (environ[i] != NULL)
// 	{
// 		if ((ft_strncmpm(environ[i], name, (ft_strlen(environ[i]))) == 0) && len)
// 			return (environ[i] + len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

static size_t get_new_length(const char* str) {
    size_t new_len = strlen(str) + 1;
    const char* p = str;
    while (*p != '\0') {
        if (*p == '$') {
            const char* var_start = p + 1;
            const char* var_end = p + 1;
            while (*var_end != '\0' && (*var_end == '_' || (*var_end >= 'a' && *var_end <= 'z') || (*var_end >= 'A' && *var_end <= 'Z') || (*var_end >= '0' && *var_end <= '9'))) {
                var_end++;
            }
            if (var_end > var_start) {
                char var_name[1024];
                size_t var_name_len = var_end - var_start;
                if (var_name_len > sizeof(var_name) - 1) {
                    return 0; // Error: variable name too long
                }
                strncpy(var_name, var_start, var_name_len);
                var_name[var_name_len] = '\0';
                char* var_value = getenv(var_name);
                if (var_value != NULL) {
                    new_len += strlen(var_value) - (var_end - var_start);
                }
                p = var_end;
            } else {
                p++;
            }
        } else {
            p++;
        }
    }
    return new_len;
}

char* replace_vars(const char* str) {
    size_t new_len = get_new_length(str);
    if (new_len == 0) {
        return NULL; // Error: variable name too long
    }
    char* new_str = malloc(new_len);
    if (new_str == NULL) {
        return NULL; // Error: out of memory
    }
    char* new_str_ptr = new_str;
    const char* p = str;
    while (*p != '\0') {
        if (*p == '$') {
            const char* var_start = p + 1;
            const char* var_end = p + 1;
            while (*var_end != '\0' && (*var_end == '_' || ft_isalnum(*var_end))) {
                var_end++;
            }
            if (var_end > var_start) {
                char var_name[1024];
                size_t var_name_len = var_end - var_start;
                strncpy(var_name, var_start, var_name_len);
                var_name[var_name_len] = '\0';
                char* var_value = getenv(var_name);
                if (var_value != NULL) {
                    size_t var_value_len = strlen(var_value);
                    memcpy(new_str_ptr, var_value, var_value_len);
                    new_str_ptr += var_value_len;
                }
                p = var_end;
            } else {
                *new_str_ptr++ = *p++;
            }
        } else {
            *new_str_ptr++ = *p++;
        }
    }
    *new_str_ptr = '\0';
    return new_str;
}




int main(int ac, char **av) {
	(void)ac;
    char str[] = "The value of PATH is $PATH and the value of FOO is $USER";
    // replace_vars(str);
    printf("%s\n", replace_vars(str));
    // printf("%s\n", str);
	// system("leaks a.out");
    return 0;
}

// int main() {
// //    int fd;
// extern char **environ;
// t_list *all = env_list();
// while ((all))		
// {
// 	printf("%s\n",(char *)(all)->content);
// 	(all) = (all)->next;
// }

// //    char *buf = NULL;
// //    char *result = ft_strdup("");
// //    while ((buf = get_next_line(0)))
// //         result = ft_strjoinn(result,buf);
// //    puts("here");
// //    printf("\n%s",result);
// //    int len = strlen(result);
// //    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
// //    if(fd == -1) {
// //       printf("Error creating file.\n");
// //       return 1;
// //    }

// //    if(write(fd, result, len) != len) {
// //       printf("Error writing to file.\n");
// //       close(fd);
// //       return 1;
// //    }
// //    printf("File created and written successfully!\n");
// 	// char str[] = ">>hello>>hi>>maro";
// 	// char *new = add_spaces_around_operators(str);
// 	// printf("%s", new);
// 	// system("leaks a.out");
// }