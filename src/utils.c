#include "minishell.h"

void	ft_list_free(t_pipex *list)
{
	if (list->com_paths)
		free(list->com_paths);
	if (list->pids)
		free(list->pids);
}

int	ft_error_msg(t_data *data, char *msg, int msg_len)
{
	data->exit_st = 1;
	write(2, msg, msg_len);
	return (1);
}

/*FOR EXPANDER*/
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
	return (new);
}
