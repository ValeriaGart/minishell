#include "../incl/minishell.h"

static int	ft_count_commands(char *s)
{
	int	count;
	int	i;
	int	q;

	i = 0;
	q = 0;
	count = 0;
	while (s[i])
	{
		if (q == 0 && is_quote(s[i]))
			q = s[i] % 2 + 1;
		else if (is_quote(s[i]) && q == s[i] % 2 + 1)
			q = 0;
		while (s[i] == PIPE && q == 0)
			i++;
		if (s[i] && s[i] != PIPE && (q == 0 || i == 0))
			count++;
		while (s[i] && (s[i] != PIPE || q != 0))
			i++;
	}
	return (count);
}

void	*ft_free_command(char **new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		free(new[i]);
		i++;
	}
	return (NULL);
}

int	ft_check_in_quote(char *s, int i)
{
	int	q;
	int	index;

	index = 0;
	q = 0;
	while (index < i)
	{
		if (q == 0 && is_quote(s[index]))
			q = s[index] % 2 + 1;
		else if (is_quote(s[index]) && q == s[index] % 2 + 1)
			q = 0;
		index++;
	}
	if (q == 0)
		return (0);
	return (1);
}

char	*ft_get_command(char *s, int j, int *i)
{
	char	*new;

	while (s[*i])
	{
		if (s[*i] == PIPE && !ft_check_in_quote(s, *i))
		{
			new = ft_substr(s, j, (*i) - j);
			(*i)++;
			if (!new)
				return (NULL);
			else
				return (new);
		}
		(*i)++;
	}
	new = ft_substr(s, j, (*i) - (j - 1));
	if (!new)
		return (NULL);
	else
		return (new);
}

char	**ft_command_split(char *s)
{
	char	**new;
	int		i;
	int		j;
	int		c;

	c = 0;
	new = ft_calloc(sizeof(char *), ft_count_commands(s) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		j = i;
		new[c] = ft_get_command(s, j, &i);
		if (!new[c])
			return (ft_free_command(new));
		c++;
	}
	return (new);
}

/*char	ft_echo_case(char *s, int *i)
{
	int		n;
	char	*ret;

	n = 0;
	while (s && s[n] && s[n] == ' ')
		n++;
	if (ft_strncmp(s + n, "echo", 4))
	{
		ret = ft_strdup(s);
		if (!ret)
			*i = 1;
		return (ret);
	}
	if (s[n] && s[n] == '"')
	{
		n++;
		if (ft_strncmp(s + n, "echo", 4))
		{

		}
	}
	return (NULL);
}*/

char	*remove_quote(char *s)
{
	char	*new;
	int		i;
	int		q;

	i = 0;
/*	new = ft_echo_case(s, &i);
	if (i != 0)
		return (NULL);
	if (new)
		return (new);*/
	new = ft_strdup("");
	q = 0;
	while (s[i])
	{
		if (q == 0 && is_quote(s[i]))
			q = s[i] % 2 + 1;
		else if (is_quote(s[i]) && q == s[i] % 2 + 1)
			q = 0;
		else
			new = ft_strjoin_char(new, s[i]);
		i++;
	}
	return (new);
}

char	**ft_remove_quotes(char **av)
{
	int		i;
	char	**new;

	i = 0;
	while (av[i])
		i++;
	new = ft_calloc(sizeof(char *), i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (av[i])
	{
		new[i] = remove_quote(av[i]);
		if (!new[i])
			return (ft_free_command(new));
		i++;
	}
	new[i] = NULL;
	ft_free_array(av);
	return (new);
}
