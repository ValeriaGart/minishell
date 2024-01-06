#include "../incl/minishell.h"

int	is_quote(int c)
{
	if (c == D || c == S)
		return (1);
	return (0);
}

int	is_open_quote(int c)
{
	static bool	is_open[2];
	int	which_quote;

	if (c == D)
		which_quote = 0;
	else if (c == S)
		which_quote = 1;
	if (c == D || c == S)
		is_open[which_quote] ^= true;
	else
		return (0);
	return (is_open[which_quote]);
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
