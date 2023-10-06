
#include "../incl/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((s1[i]) - s2[i]);
}

/*
char	**create_path(t_dlist *c_path)
{
	char	*environ;
	char	**new;
	t_dlist	*create_path;

	create_path = c_path;
	new = NULL;
	while (c_path)
	{
		if (ft_strncmp(c_path->str, "PATH", 4) == 0)
		{
			environ = c_path->str;
			break ;
		}
		c_path = c_path->next;
	}
	if (c_path != NULL)
		new = ft_split(environ, ':');
	c_path = create_path;
	return (new);
}

*/