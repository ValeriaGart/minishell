#include "../incl/minishell.h"

<<<<<<< HEAD
int	is_quote(int c)
{
	if (c == D || c == S)
		return (1);
	return (0);
}

int	ft_is_space(char s)
=======
int	ft_is_space(char s, int space)
>>>>>>> 2ec8d41dc695fea01ff2b616619f2fb3b787baf7
{
	if (space != 0)
		return (1);
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
	while (ft_is_space(s[i], 0) == 0)
		i++;
	while (s[i] && ft_is_space(s[i], 1))
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
