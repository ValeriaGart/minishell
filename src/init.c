#include "../incl/minishell.h"

int     init_pipex(t_pipex *list, t_data *data, int ac, t_tokens *toks)
{
    list->command = NULL;
    list->data = data;
	list->paths_exist = 1;
	list->here_doc_delim = NULL;
    list->tokens = toks;
    list->ac = ac;
	list->paths = NULL;
	list->paths = ft_bcheck_paths(data->env);
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
