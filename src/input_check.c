#include "../incl/minishell.h"

int	syntax_errors(char c)
{
	if (c == PIPE)
	{
		g_minishell = 2;
		ft_putendl_fd("Pipe can only be used in a full command", 2);
	}
	else if (c == D || c == S)
	{
		g_minishell = 2;
		ft_putendl_fd("Quotes error", 2);
	}
	return (2);
}

int	check_pipe(char *input, int y, int quote)
{
	int	end_str;
	int	i;

	i = 0;
	end_str = ft_strlen(input) - 1;
	while (input[i] && ft_is_space(input[i]) == 1)
		i++;
	if (input[i] == PIPE || !input[i])
		return (syntax_errors(input[i]));
	while (end_str != 0 && ft_is_space(input[end_str]))
		end_str--;
	if (input[end_str] == PIPE)
		return (syntax_errors(input[end_str]));
	y++;
	while (input[y] && ft_is_space(input[y]) == 1)
		y++;
	if (!quote && input[y] == PIPE)
		return (syntax_errors(input[y]));
	return (0);
}

int	check_open_quote(char *s)
{
	int		i;
	char	rem;

	i = 0;
	while (s[i])
	{
		if (s[i] == S || s[i] == D)
		{
			rem = s[i];
			i++;
			while (s[i] && s[i] != rem)
				i++;
			if (s[i] == '\0')
			{
				syntax_errors(S);
				return (1);
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	check_input(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (ft_is_space(s[i]) == 1)
			;
		else if (s[i] == PIPE)
		{
			if (check_pipe(s, i, quote))
				return (1);
		}
		else if (s[i] == S || s[i] == D)
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			if (check_open_quote(s))
				return (1);
		}
		i++;
	}
	return (0);
}