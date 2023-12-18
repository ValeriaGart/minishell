#include "minishell.h"

int		ft_is_echo_last(t_tokens *toks, int i)
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
		return;
	}
	*toks = next;
}

void	ft_del_com(t_pipex **list, t_tokens **tokens, int i)
{
	t_tokens	*iter;

	iter = *tokens;
	while (iter->ind_command != i)
		iter = iter->next;
	while (iter && iter->ind_command == i)
		ft_change_args(&iter);
	while (iter && iter->prev)
		iter = iter->prev;
	*tokens = iter;
	if (iter == NULL)
		(*list)->tokens = iter;
}

int	ft_newinfd(t_tokens **toks, t_pipex **list, int i)
{
	int			y;
	char		*file;

	y = 3;
	if ((*list)->redir_in != -1)
		close((*list)->redir_in);
	while ((*toks) && (*toks)->type != COM)
		*toks = (*toks)->next;
	if (!(*toks) || (*toks)->ind_command != i)
	{
		if (i == (*list)->ac - 1)
			ft_error("parse error near ", "`\\n'\n", 0);
		else
			ft_error("parse error near ", "`|'\n", 0);
		return (-5);
	}
	file = (*toks)->val;
	(*list)->redir_in = open(file, O_RDONLY);
	if ((*list)->redir_in < 0 )
	{
		perror(file);
		ft_del_com(list, &((*list)->tokens), i);
		if (i == (*list)->ac - 1)
			return (2);
		return (1);
	}
	if ((*toks)->prev->type == SEP)
		++y;
	while (--y)
		ft_change_args(toks);
	return (0);
}

int	ft_newoutfd(t_tokens **toks, t_pipex **list, int i)
{
	t_tokens	*rem_tok;
	int			y;
	char		*file;

	y = 3;
	rem_tok = *toks;
	if ((*list)->redir_out != -1)
		close((*list)->redir_out);
	while ((*toks) && (*toks)->type != COM)
		*toks = (*toks)->next;
	if (!(*toks) || (*toks)->ind_command != i)
	{
		if (i == (*list)->ac - 1)
			ft_error("parse error near ", "`\\n'\n", 0);
		else
			ft_error("parse error near ", "`|'\n", 0);
		return (-5);
	}
	file = (*toks)->val;
	if (rem_tok->val[1] != '\0')
		(*list)->redir_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		(*list)->redir_out = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if ((*list)->redir_out < 0)
	{
		perror(file);
		ft_del_com(list, &((*list)->tokens), i);
		if (i == (*list)->ac - 1)
			return (2);
		return (1);
	}
	if ((*toks)->prev->type == SEP)
		++y;
	while (--y)
		ft_change_args(toks);
	return (0);
}

int		ft_heredoc_set(t_tokens **toks, t_pipex *list)
{
	int			y;
	char		*delim;

	y = 3;
	if (list->here_doc)
	{
		free(list->here_doc_delim);
		list->here_doc = 0;
	}
	while ((*toks)->type != COM)
		*toks = (*toks)->next;
	list->here_doc = 1;
	delim = (*toks)->val;
	if ((*toks)->prev->type == SEP)
		++y;
	list->here_doc_delim = ft_strdup(delim);
	if (!list->here_doc_delim)
		return (1);
	while (--y)
		ft_change_args(toks);
	return (0);
}

//TODO: check if heredoc works and unlinks properly
void	ft_heredoc_exec(t_pipex *list)
{
	char		*delim;
	char		*buf;

	delim = list->here_doc_delim;
	list->redir_in = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (list->redir_in < 0)
		perror("heredoc");
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(STDIN_FILENO, 0);
		if (!ft_strncmp(delim, buf, ft_strlen(delim)))
			break ;
		write(list->redir_in, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	get_next_line(-1, 1);
	close(list->redir_in);
	list->redir_in = open(".heredoc", O_RDONLY);
	unlink(".heredoc");
}

//TODO: check "pwd | wc -l >"
//TODO: check "wc -l | "
int	ft_redirects(int i, t_tokens **toks_orig, t_pipex *list)
{
	t_tokens	*toks;
	int			err;

	toks = *toks_orig;
	err = 0;
	while (toks->ind_command != i)
		toks = toks->next;
	while (toks && toks->ind_command == i)
	{
		if (toks->type == REDIR_OUT)
			err = ft_newoutfd(&toks, &list, i);
		else if (toks->type == REDIR_IN)
			err = ft_newinfd(&toks, &list, i);
		else if (toks->type == HERE_DOC)
			ft_heredoc_set(&toks, list);
		if (err)
		{
			g_minishell = 1;
			if (err == -5 || i == list->ac - 1)
				return (-2);
			return (-1);
		}
		toks = toks->next;
	}
	if (list->here_doc)
		ft_heredoc_exec(list);
	return (0);
}
