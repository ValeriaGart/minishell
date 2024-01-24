#include "../incl/minishell.h"

int	ft_is_heredoc(char *new)
{
	int	i;

	i = ft_strlen(new);
	if (!i)
		return (0);
	i--;
	if (new[i] == D)
		i--;
	while (i != -1 && ft_isspace(new[i]))
		i--;
	if (i > 0 && new[i] == '<' && new[i - 1] == '<')
	{
		while (i != -1 && new[i] == '<')
			i--;
		if (i == -1 || ft_isspace(new[i]))
			return (1);
	}
	return (0);
}

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
			tmp = ft_change_buf(env_var, &buf, i);
			if (!tmp)
				save_free((char *)buf, (char *)tmp);
			free(env_var);
		}
		if (buf[i])
			i++;
	}
	return (buf);
}
