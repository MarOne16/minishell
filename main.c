# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


char* replace(char *str, char *from, char *to)
{
    char *newinput = malloc(strlen(str) + (strlen(to) - strlen(from)) + 10);
    int i = 0;
    int j;
    int off = 0;
    int z;
    int u  = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            while (str[i + 1] == '$')
            {
                newinput[i] = str[i];
                i++;
            }
            j = 0;
            z = i;
            while (str[i] != 32 && str[i] && str[i] != '$')
            {
                j++;
                i++;
                // if (str[i] == '$')
                //     break;
            }
            while (to[u])
            {
                while (to[u] != '=' && off == 0)
                {
                    if (to[u + 1] == '=')
                        off = 1;
                    u++;
                }
                newinput[z] = to[u];
                u++;
                z++;
            }
            while (str[i])
            {
                newinput[z] = str[i];
                i++;
            }
            newinput[z] = 0;
            return(newinput);
        }
        else
            newinput[i] = str[i];
        i++;
    }
    newinput[i] = 0;
    printf("\n%s\n",newinput);
    return(newinput);

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

void    ft_readline(char **env, char *input)
{
    int i = 0;
    int j;
    char *newinput = 0;
    char *need = malloc(sizeof(char) * getsize(input) + 1);
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
                    break;
            }
            break;
        }
        i++;
    }
    i = 0;
    while (env[i])
    {
        if (strstr(env[i],need) != NULL)
        {
            newinput = replace(input,need,env[i]);
            printf("\n%s\n",newinput);
        }
        i++;
    }
    
}

int main(int argc, char const *argv[], char **env)
{
    
    // (void)argv;
    // (void)argc;
    // char *input = NULL;
    // int i = 0;
    // while ((input = readline("prompt : ")))
    // {
    //     ft_readline(env,input);
    // }
    char str[] = "echo | hello mar";
    char need[] = "hello";
    printf("%s\n",strstr(str,need));
    printf("%s",need); 
    return 0;
}
