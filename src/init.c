#include "../incl/minishell.h"

//frees in loop parent stuff that is dynamically allocated
void	ft_free_in_loop(t_pipex *list)
{
	if (list->redir_out != -1)
	{
		close(list->redir_out);
		list->redir_out = -1;
	}
	if (list->redir_in != -1)
	{
		close(list->redir_in);
		list->redir_in = -1;
	}
}

//TODO: check if close redir files everywhere when needed
//TODO: check if after del unvalid redirect there is nothing saved in pipe before
int	ft_init_list_loop(t_pipex *list, int i, int reidir_err)
{
	list->builtin = 0;
	list->here_doc = 0;
	list->redir_in = -1;
	list->redir_out = -1;
	reidir_err = ft_redirects(i, &(list->tokens), list);
	if (reidir_err)
		return (reidir_err);
	list->args = ft_tok_to_args(list->tokens, i);
	if (!list->args)
	{
		ft_error_msg("Malloc failed\n", 15);
		close(list->pipes[0]);
		close(list->pipes[1]);
		return (1);
	}
	if (!is_builtin(list->tokens, i))
	{
		list->command = ft_gimme_com(list->tokens, list, i);	
		if (!list->command)
			return (1);
	}
	else
		list->builtin = 1;
	return (0);
}

int     init_pipex(t_pipex *list, t_data *data, t_tokens *toks)
{
	list->redir_in = -1;
	list->redir_out = -1;
    list->command = NULL;
    list->data = data;
	list->paths_exist = 1;
	list->here_doc_delim = NULL;
    list->tokens = toks;
    list->ac = ft_find_tok(toks, -1);
	list->paths = NULL;
	list->paths = ft_bcheck_paths(data->env);
	list->com_paths = NULL;
	if (list->paths)
	{
	    list->com_paths = ft_split(list->paths, ':');
		if (!list->com_paths)
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
