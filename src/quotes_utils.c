#include "../incl/minishell.h"

int quote_exist(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\'' || s[i] != '\"')
			return (1);
		i++;
	}
	return (0);
}

int	ft_execute_symbols(char *str, int exc, int i)
{
	int	j;
    int n;

	if (exc == 1)
		return (i + 1);
	j = exc;
	if (exc % 2 == 0)
		while (j-- != exc / 2)
			write(1, "\\", 1);
	else
	{
		j = exc;
		while (j-- != (exc / 2) + 1)
			write(1, "\\", 1);
	}
    n = i + exc;
	return (n);
}

void	no_quote_execute(char *s, int i, int j, int double_q)
{
	int	q;

	q = quote_exist(s);
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			double_q = 1;
		if ((s[i] == ' ' && s[i + 1] == ' ' && q == 1) || s[i] == '\'')
			while (s[i] == ' ')
				i++;
		j = i;
		if (s[i] == '\'')
		{
			while (s[j] == '\'')
				j++;
			i = ft_execute_symbols(s, j, i);
		}
		if (s[i] != '"' && s[i] != 39)
			printf("%c", s[i]);
		else if (s[i] == 39)
			if (double_q == 1)
				printf("%c", s[i]);
		i++;
	}
}
