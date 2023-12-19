#include "minishell.h"

int		ft_find_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s && s[i] == c)
		return (i);
	return (-1);
}

int	ft_error_msg(char *msg, int msg_len)
{
	g_minishell = 1;
	write(2, msg, msg_len);
	return (1);
}

/*FOR EXPANDER:
we accept cases: after $ things can printable*/
int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}
