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
