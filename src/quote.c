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
		return (1);
	return (0);
}

int	ft_quote_condition(char **val, int y, char *str, int *i)
{
	char	*value;
	char	meet_again;

	meet_again = str[y];
	value = *val;
	y++;
	while (str[y] != meet_again)
	{
		*i = *i + 1;
		value[*i] = str[y];
		y++;
	}
	y++;
	return (y);
}
