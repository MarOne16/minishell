#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*add_spaces_around_operators(char *s)
{
	size_t	len = strlen(s);
	char	*result = malloc(3 * len + 1);
	size_t	i = 0, j = 0;

	while (i < len)
	{
		if (s[i] == '<' || s[i] == '>')
		{
			int	count = 0;
			while (i < len && (s[i] == '<' || s[i] == '>'))
			{
				count++;
				i++;
			}
			if (count == 1 || count == 2)
			{
				result[j++] = ' ';
				for (int k = 0; k < count; k++)
					result[j++] = s[i - count + k];
				result[j++] = ' ';
			}
			else
				for (int k=0; k<count; ++k)
					result[j++]=s[i-count+k];
        }
        else
            result[j++]=s[i++];
    }
    result[j]='\0';
    return result;
}

int main() {
    char *input_string = "a<b>>c<<d>e >>>echo";
    char *output_string = add_spaces_around_operators(input_string);
    printf("%s\n", output_string);  // Output: "a < b >> c << d > e"
    free(output_string);
    return 0;
}