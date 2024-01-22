#include "minishell.h"

int	ft_newinfd(t_tokens **toks, t_pipex **list, int i)
{
	int			y;
	char		*file;

	y = 3;
	*toks = ft_open_file(*toks, *list, i, 0);
	if (!*toks)
		return (-5);
	file = (*toks)->val;
	(*list)->redir_in = open(file, O_RDONLY);
	if ((*list)->redir_in < 0)
	{
		perror(file);
		ft_del_com(list, toks, y, 0);
		//TODO: (do you still need this?) ft_del_com(list, &((*list)->tokens), i, 1);
		if (i == (*list)->ac - 1)
			return (2);
		return (1);
	}
	ft_del_com(list, toks, y, 0);
	return (0);
}

int	ft_newoutfd(t_tokens **toks, t_pipex **list, int i)
{
	t_tokens	*rem_tok;
	int			y;
	char		*file;

	y = 3;
	rem_tok = *toks;
	*toks = ft_open_file(*toks, *list, i, 1);
	if (!*toks)
		return (-5);
	file = (*toks)->val;
	if (rem_tok->val[1] != '\0')
		(*list)->redir_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		(*list)->redir_out = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if ((*list)->redir_out < 0)
	{
		perror(file);
		ft_del_com(list, toks, y, 0);
		//TODO: ( do you still need this?)ft_del_com(list, &((*list)->tokens), i, 1);
		if (i == (*list)->ac - 1)
			return (2);
		return (1);
	}
	ft_del_com(list, toks, y, 0);
	return (0);
}

int	ft_last_word(int i, t_tokens *toks, t_tokens *toks_orig)
{
	if (!toks_orig || !toks)
		return (1);
	toks = toks->next;
	if (!toks || toks->ind_command != i)
		return (1);
	return (0);
}

void	check_token_type(t_tokens **toks, t_pipex **list, int *i, int *err)
{
	if ((*err) != 1 && (*toks)->type == FD_REDIR)
	{
		*err = ft_newoutfd(toks, list, *i);
		if (*err)
			return ;
		(*list)->fd_redir_out = ft_atoi((*toks)->val);
		dup2((*list)->redir_out, (*list)->fd_redir_out);
		ft_change_args(toks);
		close((*list)->redir_out);
		(*list)->redir_out = -1;
	}
	else if ((*toks)->type == REDIR_OUT && (*err) != 1)
		*err = ft_newoutfd(toks, list, *i);
	else if ((*toks)->type == REDIR_IN && (*err) != 1)
		*err = ft_newinfd(toks, list, *i);
	else if ((*toks)->type == HERE_DOC)
		*err = ft_heredoc_set(toks, *list, *i, *err);
}

int	ft_redirects(int i, t_tokens *toks, t_pipex *list)
{
	int			err;

	err = 0;
	toks = ft_point_to_needed_tok(toks, i, 0, 0);
	while (toks && toks->ind_command == i)
	{
		list->block_incr_redir = 0;
		check_token_type(&toks, &list, &i, &err);
		if (err && (err != 1 || ft_last_word(i, toks, list->tokens)))
		{
			if (err != -5)
				g_minishell = 1;
			//TODO: if malloc failed, is 2d condition right? ( do you still need this?)
			if (err == -5 || i == list->ac - 1)
				return (-2);
			return (-1);
		}
		if (!list->tokens)
			toks = NULL;
		if (toks && !list->block_incr_redir)
			toks = toks->next;
	}
	return (0);
}
