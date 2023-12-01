#include "../incl/minishell.h"

void	ft_list_loop_free(t_pipex *list)
{
	int	i;

	i = 0;
	if (list->command)
		free(list->command);
	list->command = NULL;
	if (list->args)
	{
		while (list->args[i])
		{
			free(list->args[i]);
			i++;
		}
		free(list->args);
	}
	list->args = NULL;
}

void	ft_free_av(char **av)
{
	int	i;

	i = 0;
	while(av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	*save_free(void *s1, void *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s2)
		return ((char *)s1);
	if (!s1)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		new[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		new[i + j] = s2[j];
	new[i + j] = '\0';
	save_free((void *)s1, (void *)s2);
	return (new);
}

void	*ft_free_array(char **array)
{
	int i = 0;
	if (!array)
		return (NULL);
	while (array[i])
	{
		save_free((void *)array[i], NULL);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}
