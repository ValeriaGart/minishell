#include "../incl/minishell.h"

int     init_pipex(t_pipex *list, t_data *data, int ac, t_tokens *toks)
{
    list->command = NULL;
    list->data = data;
	list->here_doc_delim = NULL;
    list->tokens = toks;
    list->ac = ac;
    list->paths = ft_bcheck_paths(data->env);
	if (!list->paths)
		return (1);
    list->com_paths = ft_split(list->paths, ':');
	if (!list->com_paths)
		return (ft_error_msg("Malloc failed\n", 15));
	list->pids = malloc(list->ac * sizeof(pid_t));
	if (!list->pids)
	{
		ft_list_free(list);
		return (ft_error_msg("Malloc failed\n", 15));
	}
	return (0);
}
