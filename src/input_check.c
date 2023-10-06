#include "../incl/minishell.h"

int	syntax_errors(t_data *d, char c)
{
	if (c == PIPE)
	{
		ft_putendl_fd("parse error near `|'", 2);
		d->exit = 2;
		return (2);
	}
	else if (c == '<' || c == '>')
	{
		ft_putendl_fd("error redirection", 2);
		d->exit = 2;
		return (2);
	}
	else if (c == D || c == S)
	{
		ft_putendl_fd("Quotes error", 2);
		d->exit = 2;
		return (2);
	}
	return (0);
}

/*I check:
		1st position is PIPE->error
		last position is PIPE->error
		2 PIPE together -> error*/
int	check_pipe(t_data *d, char *input)
{
	int	end_str;
	int	i;

	end_str = ft_strlen(input) - 1;
	i = 0;
	if (input[0] == PIPE)
		return (syntax_errors(d, input[i]));
	else if (input[end_str] == PIPE)
		return (syntax_errors(d, input[i]));
	while (ft_is_space(input[i], i))
		i++;
	if (input[i] == PIPE && input[i + 1] == PIPE)
		return (syntax_errors(d, input[i]));
	return (0);
}
/*	after redirection is NULL -> error
	after 1st rediction is | or redirections -> error
*/

int	check_redirect(t_data *d, char *s, char redirect)
{
	int	i;

	i = 0;
	if (s[i] == redirect && s[i + 1] != redirect)
		i++;
	while (ft_is_space(s[i], i))
		i++;
	if (s[i] == '\0')
		return (syntax_errors(d, '\n'));
	if (s[i] == PIPE || s[i] == '<' || s[i] == '>')
		return (syntax_errors(d, s[i]));
	return (0);
}

int	check_input(t_data *d, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_is_space(s[i], i))
			i++;
		else if (s[i] == S || s[i] == D)
		{
			printf("hello\n");
			return (check_open_quote(d, s));
		}
		else if (s[i] == PIPE)
			return (check_pipe(d, s));
		else if (s[i] == '>' || s[i] == '<')
			return (check_redirect(d, s, s[i]));
		else
			i++;
	}
	return (0);
}
