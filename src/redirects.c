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
		//ft_del_com(list, &((*list)->tokens), i, 1);
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
		//ft_del_com(list, &((*list)->tokens), i, 1);
		if (i == (*list)->ac - 1)
			return (2);
		return (1);
	}
	ft_del_com(list, toks, y, 0);
	return (0);
}

void	ft_heredoc_exec(char *delim, t_pipex *list)
{
	char		*buf;

	buf = NULL;
	list->redir_in = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (list->redir_in < 0)
		perror("heredoc");
	while (g_minishell != 130)
	{
		sig_handel(3);
		signal(SIGINT, get_sig_heredoc);
		buf = readline("> ");
		if (!buf || (!ft_strncmp(delim, buf, ft_strlen(delim)) && ft_strlen(delim) == ft_strlen(buf)))
			break ;
		write(list->redir_in, buf, ft_strlen(buf));
		if (g_minishell != 130)
		{
			write(list->redir_in, "\n", 1);
			free(buf);
			buf = NULL;
		}
	}
	close(list->redir_in);
	list->redir_in = open(".heredoc", O_RDONLY);
	if (!buf && g_minishell != 130)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delim, 2);
		ft_putstr_fd("')\n", 2);
		return ;
	}
	if (g_minishell == 130)
	{
		list->heredoc_c = 1;
		g_minishell = 0;
	}
	if (buf)
		free(buf);
}

int	ft_heredoc_set(t_tokens **toks, t_pipex *list, int i, int err)
{
	int			y;
	char		*delim;

	y = 3;

	g_minishell = 0;
	if (list->redir_in != -1)
	{
		unlink(".heredoc");
		close(list->redir_in);
	}
	if (list->here_doc)
		list->here_doc = 0;
	*toks = ft_syntax_err_redir(*toks, i);
	if (!*toks)
		return (-5);
	list->here_doc = 1;
	delim = (*toks)->val;
	if ((*toks)->prev->type == SEP)
		++y;
	ft_heredoc_exec((*toks)->val, list);
	while (--y)
		ft_change_args(toks);
	if (!*toks || (*toks)->prev == NULL)
		list->tokens = *toks;
	if (err == 1)
		return (err);
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

//TODO: check "pwd | wc -l >"
//TODO: check "wc -l | "
//TODO: < < ho cat
//TODO: check <<<<<< things like that
int	ft_redirects(int i, t_tokens *toks, t_pipex *list)
{
	int			err;

	err = 0;
	toks = ft_point_to_needed_tok(toks, i, 0, 0);
	while (toks && toks->ind_command == i)
	{
		if (toks->type == REDIR_OUT && err != 1)
			err = ft_newoutfd(&toks, &list, i);
		else if (toks->type == REDIR_IN && err != 1)
			err = ft_newinfd(&toks, &list, i);
		else if (toks->type == HERE_DOC)
			err = ft_heredoc_set(&toks, list, i, err);
		if (err && (err != 1 || ft_last_word(i, toks, list->tokens)))
		{
			if (err != -5)
				g_minishell = 1;
			//TODO: if malloc failed, is 2d condition right? :
			if (err == -5 || i == list->ac - 1)
				return (-2);
			return (-1);
		}
		if (!list->tokens)
			toks = NULL;
		if (toks)
			toks = toks->next;
	}
	return (0);
}
