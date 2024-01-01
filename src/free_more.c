#include "../incl/minishell.h"

void	ft_list_free(t_pipex *list)
{
	if (list->here_doc)
		unlink(".heredoc");
	list->com_paths = ft_free_command(list->com_paths);
	if (list->pids)
		free(list->pids);
	if (list->redir_out != -1)
		close(list->redir_out);
	if (list->redir_in != -1)
		close(list->redir_in);
}

char	*ft_strjoin_char(char *str, char c)
{
	unsigned int	i;
	char			*new;

	if (!str)
		return (save_free((void *)str, NULL));
	i = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (new)
	{
		new[i + 1] = '\0';
		new[i] = c;
		while (i--)
			new[i] = str[i];
	}
	free(str);
	return (new);
}

char	*ft_free_new(char *new)
{
	if (new)
		free(new);
	return (NULL);
}

t_tokens	*ft_free_toks(t_tokens *toks)
{
	if (!toks)
		return (NULL);
	while (toks && toks->next)
		toks = toks->next;
	while (toks && toks->prev)
	{
		if (toks->val)
			free(toks->val);
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
	}
	if (toks && toks->val)
		free(toks->val);
	if (toks)
		free(toks);
	return (NULL);
}
