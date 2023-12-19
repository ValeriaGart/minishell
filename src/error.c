#include "minishell.h"

int	ft_export_error(t_tokens *toks, char *val, int ind)
{
	int	i;

	i = 0;
	while (toks && toks->ind_command == ind)
	{
		if (toks->type == COM)
		{
			i = 0;
			while (toks->val[i])
			{
				if (!ft_isalpha(toks->val[i]))
				{
					write(2, "minishell: export: `", 20);
					ft_putstr_fd(val, 2);
					write(2, "': not a valid identifier\n", 26);
					g_minishell = 1;
					break ;
				}
				i++;
			}
		}
		toks = toks->next;
	}
	return (1);
}

int	ft_error_screen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '!' && str[i + 1])
			return (ft_error(str, ": event not found\n", i));
		i++;
	}
	return (0);
}

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

