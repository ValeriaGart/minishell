#include "minishell.h"

int	ft_is_echo_last(t_tokens *toks, int i)
{
	t_tokens	*if_last;

	if_last = toks;
	if_last = if_last->next;
	while (if_last && if_last->type == SEP)
		if_last = if_last->next;
	if (!if_last || if_last->ind_command != i)
		return (0);
	if (toks)
		toks = toks->prev;
	while (toks && toks->prev && toks->type != COM)
		toks = toks->prev;
	if (toks && !ft_strncmp(toks->val, "echo", 4) && ft_strlen(toks->val) == 4)
		return (1);
	return (0);
}

void	ft_change_args(t_tokens **toks)
{
	t_tokens	*prev;
	t_tokens	*next;

	next = (*toks)->next;
	prev = (*toks)->prev;
	if ((*toks)->val)
		free((*toks)->val);
	free(*toks);
	if (next)
		next->prev = prev;
	if (prev)
	{
		prev->next = next;
		*toks = prev;
		return ;
	}
	*toks = next;
}

t_tokens	*ft_open_file(t_tokens *toks, t_pipex *list, int i, int out)
{
	if (out)
	{
		if (list->redir_out != -1)
			close(list->redir_out);
	}
	else
	{
		if (list->redir_in != -1)
			close(list->redir_in);
	}
	while (toks && toks->type != COM)
		toks = toks->next;
	if (!toks || toks->ind_command != i)
	{
		if (i == list->ac - 1)
			ft_error("parse error near ", "`\\n'\n", 0);
		else
			ft_error("parse error near ", "`|'\n", 0);
		return (NULL);
	}
	return (toks);
}

void	ft_del_com(t_pipex **list, t_tokens **tokens, int i, int completely)
{
	t_tokens	*iter;

	iter = *tokens;
	if (completely)
	{
		while (iter->ind_command != i)
			iter = iter->next;
		while (iter && iter->ind_command == i)
			ft_change_args(&iter);
		while (iter && iter->prev)
			iter = iter->prev;
		*tokens = iter;
		if (iter == NULL)
			(*list)->tokens = iter;
		return ;
	}
	if (iter->prev->type == SEP)
		++i;
	while (--i)
		ft_change_args(&iter);
}
