#include "minishell.h"

t_tokens	*ft_syntax_err_redir(t_tokens *toks, int i)
{
	toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (!toks || toks->ind_command != i || toks->type != COM)
	{
		if (!toks)
			ft_error("syntax error near unexpected token ", "`\\n'\n", 0);
		else if (toks->ind_command != i)
			ft_error("syntax error near unexpected token ", "`|'\n", 0);
		else
		{
			ft_error("syntax error near unexpected token ", "`", 0);
			ft_putstr_fd(toks->val, 2);
			ft_putstr_fd("'\n", 2);
		}
		g_minishell = 2;
		return (NULL);
	}
	return (toks);
}

int	ft_redirout_no_com(t_tokens *toks, int i, t_pipex *list, int err)
{
	if (err)
		return (err);
	while (toks && toks->ind_command != i)
		toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (!toks && list->redir_out != -1)
		return (-2);
	if (!toks)
		return (-2);
	return (0);
}

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
	if (!iter)
		(*list)->tokens = NULL;
	if (iter && iter->prev == NULL)
		(*list)->tokens = iter;
}
