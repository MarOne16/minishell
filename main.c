#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static int count_words(char *str, char c, int *hash, size_t len)
{
    int count = 0;
    size_t i = 0;

    while (str[i])
    {
        if (str[i] != c && (hash[i - len] == 0))
        {
            count++;
            while (str[i] && str[i] != c && (hash[i - len] == 0))
                i++;
        }
        else
        {
            i++;
        }
    }

    return count;
}

char **ft_split_hash(char *str, char c, int *hash, size_t len)
{
    int num_words = count_words(str, c, hash, len);
    char **words = malloc((num_words + 1) * sizeof(char *));
    if (!words)
        return NULL;

    int i = 0;
    size_t j = 0;
    while (str[j])
    {
        if (str[j] != c && (hash[j - len] == 0))
        {
            char *start = &str[j];
            while (str[j] && str[j] != c && (hash[j - len] == 0))
                j++;

            size_t word_len = j - (start - str);
            char *word = malloc((word_len + 1) * sizeof(char));
            if (!word)
                return NULL;

            memcpy(word, start, word_len);
            word[word_len] = '\0';
            words[i++] = word;
        }
        else
        {
            j++;
        }
    }
    words[i] = NULL;
    return words;
}



#include <stdio.h>

int main(void)
{
    char *str = "echo >> \"hello< word\"";
    int hash[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
    char **words = ft_split_hash(str, ' ', hash, strlen(str));
	// puts("here");
    if (!words)
    {
        printf("Error: failed to split string\n");
        return 1;
    }

    for (int i = 0; words[i] != NULL; i++)
    {
        printf("%s\n", words[i]);
        free(words[i]);
    }

    free(words);

    return 0;
}
