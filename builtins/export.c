#include "../incl/minishell.h"

int	ft_check_before_equal(char *val)
{
	int	i;

	i = 0;
	if (val[i] && !ft_isalpha(val[i]) && val[i] != '_')
		return (1);
	while (val[i])
	{
		if (val[i] == '=')
			return (0);
		if (!ft_isalnum(val[i]) && val[i] != '_')
			return (1);
		i++;
	}
	return (1);
}

void	ft_repoint_env(t_env *tmp, t_env **new)
{
	if (tmp != *new)
		while (tmp->next != *new)
			tmp = tmp->next;
	if (tmp == *new)
	{
		free((*new)->str);
		(*new)->str = NULL;
	}
	else
	{
		tmp->next = (*new)->next;
		free ((*new)->str);
		free (*new);
		*new = NULL;
	}
}

void	what_is_this(char *str, int *y, int *q)
{
	str[*y] = D;
	*q = -1;
	++(*y);
}

char	*ft_cpyval(char *val, char *new)
{
	char	*str;
	int		i;
	int		y;
	int		q;

	i = -1;
	y = 0;
	q = 0;
	str = new;
	while (val[++i])
	{
		if (ft_isspace(val[i]) && q > 0)
			what_is_this(str, &y, &q);
		str[y] = val[i];
		if (val[i] == '=' && !q)
		{
			str[++y] = D;
			q = 1;
		}
		++y;
	}
	if (q > 0)
		str[y] = D;
	return (str);
}

int	ft_check_after_equal(t_env *env, char *val)
{
	int	i;

	i = 0;
	(void)env;
	while (val[i])
	{
		if (val[i] == '=')
			break ;
		i++;
	}
	while (val[i])
	{
		if (val[i] == '!' && val[i + 1])
			return (ft_error(val, ": event not found\n", i));
		i++;
	}
	return (0);
}
