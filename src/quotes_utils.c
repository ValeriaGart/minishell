
#include "../incl/minishell.h"

int	is_quote(int c)
{
	if (c == D || c == S)
		return (1);
	return (0);
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

char	*ft_strjoin_char(char *str, char c)
{
	unsigned int	i;
	char			*new;

	if (!str)
		return (save_free((void *)str, NULL));
	i = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	new[i + 1] = '\0';
	new[i] = c;
	while (i--)
		new[i] = str[i];
	free(str);
	// printf("%s\n", new);
	return (new);
}
