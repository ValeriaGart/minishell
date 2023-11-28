#include "minishell.h"

int		ft_error(char *val, char *error, int  i)
{
	write(2, "minishell: ", 11);
	while (val[i])
	{
		if (val[i] == ';')
			break;
		write(2, &val[i], 1);
		i++;
	}
	ft_putstr_fd(error, 2);
	return (1);
}
