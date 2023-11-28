#include "../incl/minishell.h"

int	syntax_errors(char c)
{
	if (c == PIPE)
	{
		minishell_global = 2;
		ft_putendl_fd("Pipe can only be used in full comnand", 2);
	}
	else if (c == '<' || c == '>')
	{
		minishell_global = 2;
		ft_putendl_fd("Error redirection", 2);
	}
	else if (c == D || c == S)
	{
		minishell_global = 2;
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

/*	after redirection is NULL -> error
	after 1st rediction is | or redirections -> error
	i at 1st redirect position*/
int	check_redirect(char *s, char redirect)
{
	int	i;

	i = 0;
	i++;
	if (s[i] == redirect && s[i + 1] != redirect)
		i++;
	while (ft_is_space(s[i]) == 1)
		i++;
	if (s[i] == '\0')
		return (syntax_errors('\n'));
	if (s[i] == PIPE || s[i] == '<' || s[i] == '>')
		return (syntax_errors(s[i]));
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
			if (check_pipe(s) == 1)
				return (1);
		}
		else if (s[i] == '>' || s[i] == '<')
		{
			if (check_redirect(s, s[i]) == 1)
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