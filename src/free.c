#include "../incl/minishell.h"

int	free_n_exit(t_data *d, int i)
{
	// ft_free_prompt(d);
	if (d->pid != NULL)
		free(d->pid);
	free(d);
	if (i == 127)
		ft_putstr_fd(": Change other commands, mate\n", 2);
	rl_clear_history();
	exit(i);
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
