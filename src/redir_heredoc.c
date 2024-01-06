#include "minishell.h"

void	error_ms_out(char *delim, t_pipex *list, char *buf)
{
	if (!buf && g_minishell != 130)
	{
		ft_putstr_fd("minishell: warning: ", 2);
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
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
		if (!buf || (!ft_strncmp(delim, buf, ft_strlen(delim))
				&& ft_strlen(delim) == ft_strlen(buf)))
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
	error_ms_out(delim, list, buf);
}

void	heredoc_first_set(t_pipex *list)
{
	if (list->redir_in != -1)
	{
		unlink(".heredoc");
		close(list->redir_in);
	}
	if (list->here_doc)
		list->here_doc = 0;
}

int	ft_heredoc_set(t_tokens **toks, t_pipex *list, int i, int err)
{
	int			y;

	y = 3;
	g_minishell = 0;
	heredoc_first_set(list);
	*toks = ft_syntax_err_redir(*toks, i);
	if (!*toks)
		return (-5);
	list->here_doc = 1;
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
