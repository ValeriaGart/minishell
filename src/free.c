#include "../incl/minishell.h"

void	ft_list_loop_free(t_pipex *list, int i, int iter)
{
	if (list->command)
		free(list->command);
	list->command = NULL;
	if (list->redir_out != -1)
		close(list->redir_out);
	if (list->redir_in != -1)
		close(list->redir_in);
	if (list->args)
	{
		while (list->args[iter])
		{
			list->args[iter] = NULL;
			iter++;
		}
		free(list->args);
	}
	list->args = NULL;
	if (list->rem_fd != -1)
		close(list->rem_fd);
	if (i < list->ac - 1)
		list->rem_fd = list->pipes[0];
	if (list->ac != 1)
		close(list->pipes[1]);
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

	if (s2[0] == '\0')
		return ((char *)s1);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new)
	{
		i = -1;
		while (s1[++i] != '\0')
			new[i] = s1[i];
		j = -1;
		while (s2[++j] != '\0')
			new[i + j] = s2[j];
		new[i + j] = '\0';
	}
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
