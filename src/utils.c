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