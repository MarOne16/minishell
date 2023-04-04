# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
	#include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#include <stdlib.h>




int main() {
	char str[] = "echo $PATH and$USER";
// 	int *hash = calloc(ft_strlen(str),4);
//   char *strr = replace_env_vars(str);
  printf("%s",replace_env_vars(str));
// for (size_t i = 0; i < strlen(str); i++)
// {
// 	printf("%d",hash[i]);
// }

	return 0;
}