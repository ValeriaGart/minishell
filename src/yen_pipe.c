#include "../incl/minishell.h"

int invalid_pipe(char *s)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (s[i])
    {
        if (s[i] == '|')
            j++;
        if (s[i] == '|')
            k++;
        i++;
    }
    if (j == k)
        return (0);
    return (1);
}