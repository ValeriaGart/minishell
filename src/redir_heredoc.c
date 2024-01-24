#include "minishell.h"

char	*ft_change_buf(char *env_var, char **buf, int i)
{
	char	*str1;
	char	*str2;
	int		aft_exp;

	aft_exp = i;
	while ((*buf)[aft_exp] && !ft_isspace((*buf)[aft_exp])
		&& (*buf)[aft_exp] != S && (*buf)[aft_exp] != D)
		aft_exp++;
	str1 = ft_calloc(i + 1, sizeof(char));
	if (!str1)
		return (NULL);
	ft_strlcpy(str1, *buf, i + 1);
	str2 = ft_strjoin(str1, env_var);
	free(str1);
	if (!str2)
		return (NULL);
	str1 = ft_strjoin(str2, (*buf) + aft_exp);
	free(str2);
	if (!str1)
		return (NULL);
	free(*buf);
	*buf = str1;
	return (*buf);
}

void	not_ctr_c(t_pipex **list, char **buf)
{
	if (g_minishell != 130)
	{
		write((*list)->redir_in, "\n", 1);
		free(*buf);
		(*buf) = NULL;
	}
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
		buf = ft_expand_heredoc(buf, ft_strlen(buf), list->data);
		write(list->redir_in, buf, ft_strlen(buf));
		not_ctr_c(&list, &buf);
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
