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

/*
	1st position is PIPE->error
	2 PIPE together -> error
*/
int	check_pipe(char *input)
{
	int	end_str;
	int	i;

	i = 0;
	end_str = ft_strlen(input) - 1;
	if (input[0] == PIPE)
		return (syntax_errors(input[i]));
	else if (input[end_str] == PIPE)
		return (syntax_errors(input[end_str]));
	while (ft_is_space(input[i]) == 1)
		i++;
	if (input[i] == PIPE && input[i + 1] == PIPE)
		return (syntax_errors(input[i]));
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

	i = 0;
	while (s[i])
	{
		if (ft_is_space(s[i]) == 1)
			;
		else if (s[i] == PIPE)
		{
			if (check_pipe(s))
				return (1);
		}
		else if (s[i] == S || s[i] == D)
		{
			if (check_open_quote(s))
				return (1);
		}
		i++;
	}
	return (0);
}