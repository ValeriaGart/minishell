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

// if i == 1 -> "not set" , else -> "No such file or directory"
void	ft_error_cd(char *str, int i)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	if (i == 1)
		ft_putstr_fd(": not set\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

