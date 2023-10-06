
#include "../incl/minishell.h"

int	quote_exist(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != S || s[i] != D)
			return (1);
		i++;
	}
	return (0);
}
