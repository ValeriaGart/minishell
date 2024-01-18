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

char *ft_get_var_no_quote(char *buf, t_data *data, int ind)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_get_var(&buf[ind + 1], data);
	if (!str)
		return (NULL);
	if (!str[i])
		return (str);
	i++;
	while (str[i] && str[i] != D)
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i] = '\0';
	str[i - 1] = '\0';
	return (str);
}

char	*ft_expand_heredoc(char *buf, int buf_len, t_data *data)
{
	char	*tmp;
	char	*env_var;
	int		i;

	i = 0;
	tmp = NULL;
	env_var = NULL;
	while (buf && buf[i] && i < buf_len)
	{
		if (buf[i] == '$' && ft_isalnum(buf[i + 1]))
		{
			env_var = ft_get_var_no_quote(buf, data, i);
			if (!env_var)
				return (buf);
			//if (env_var[0] != '\0')
			//{
			tmp = ft_change_buf(env_var, &buf, i);
			if (!tmp)
				save_free((char *)buf, (char *)tmp);
			//}
			free(env_var);
		}
		if (buf[i])
			i++;
	}
	return (buf);
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
