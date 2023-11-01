#include "../incl/minishell.h"

int	is_quote(int c)
{
	if (c == D || c == S)
		return (1);
	return (0);
}

int	ft_is_space(char s)
{
	if (s == 32)
		return (0);
	return (1);
}

int	check_open_quote(t_data *d, char *s)
{
	int	q;
	int	i;

	q = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == S || s[i] == D)
		{
			if (q == 0)
				q = s[i] % 2 + 1;
			else if (q == s[i] % 2 + 1)
				q = 0;
		}
		i++;
	}
	if (q != 0)
		return (syntax_errors(d, D));
	return (0);
}
