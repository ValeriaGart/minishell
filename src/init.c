#include "../incl/minishell.h"

int	init_part_list(t_pipex *list)
{
	list->heredoc_c = 0;
	list->builtin = 0;
	list->here_doc = 0;
	list->redir_in = -1;
	list->redir_out = -1;
	list->args = NULL;
	list->command = NULL;
	return (0);
}

//TODO: check if close redir files everywhere when needed
//TODO: check if after del unvalid redirect there is nothing 
//saved in pipe before
int	ft_init_list_loop(t_pipex *list, int i, int reidir_err)
{
	init_part_list(list);
	reidir_err = ft_redirects(i, list->tokens, list);
	reidir_err = ft_redirout_no_com(list->tokens, i, list, reidir_err);
	if (reidir_err)
		return (reidir_err);
	list->args = ft_tok_to_args(list->tokens, i, 0);
	if (!list->args)
		return (1);
	if (!is_builtin(list->tokens, i))
	{
		list->command = ft_gimme_com(list->tokens, list, i);
		if (!list->command)
		{
			list->args = ft_free_command(list->args);
			return (1);
		}
	}
	else
		list->builtin = 1;
	return (0);
}

void	ft_init_pipex(t_pipex *list, t_data *data, t_tokens *toks)
{
	list->rem_fd = -1;
	list->redir_in = -1;
	list->redir_out = -1;
	list->command = NULL;
	list->data = data;
	list->paths_exist = 1;
	list->tokens = toks;
	list->ac = ft_find_tok(toks, -1);
	list->paths = NULL;
	list->pids = NULL;
	list->com_paths = NULL;
}

int	init_malloc_pipex(t_pipex *list, t_data *data, t_tokens *toks)
{
	ft_init_pipex(list, data, toks);
	list->paths = ft_bcheck_paths(data->env);
	if (!list->paths)
		return (ft_error_msg("Malloc failed\n", 15));
	list->com_paths = ft_split(list->paths, ':');
	if (!list->com_paths)
	{
		ft_list_free(list);
		return (ft_error_msg("Malloc failed\n", 15));
	}
	list->pids = malloc(list->ac * sizeof(pid_t));
	if (!list->pids)
	{
		ft_list_free(list);
		return (ft_error_msg("Malloc failed\n", 15));
	}
	return (0);
}
