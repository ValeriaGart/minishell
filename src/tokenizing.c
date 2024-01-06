#include "../incl/minishell.h"

int	ft_quotecho_condition(char **val, int y, char *str, int *i)
{
	char	*value;
	char	meet_again;

	meet_again = str[y];
	value = *val;
	*i = *i + 1;
	value[*i] = str[y];
	y++;
	while (str[y] != meet_again)
	{
		*i = *i + 1;
		value[*i] = str[y];
		y++;
	}
	*i = *i + 1;
	value[*i] = str[y];
	y++;
	return (y);
}

t_tokens	*ft_new_token(int i, int *y, char **strs, int redir)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens));
	if (!new_tok)
		return (NULL);
	if (redir == -1)
		new_tok->val = ft_tok_val(strs[i], y, 0, 0);
	else
		new_tok->val = ft_tok_val(strs[i], y, 1, redir);
	if (!new_tok->val)
	{
		free(new_tok);
		return (NULL);
	}
	new_tok->type = ft_tok_type(new_tok->val, redir);
	new_tok->ind_command = i;
	return (new_tok);
}

void	ft_if_echo_redir(int *echo, int *redir, t_tokens *toks, int ind)
{
	if (toks->type == COM && !ft_strncmp(toks->val, "echo", 4)
		&& ind < 2 && ft_strlen(toks->val) == 4)
		(*echo)++;
	if (toks->type == COM && !ft_strncmp(toks->val, "/bin/echo", 9)
		&& ind < 2 && ft_strlen(toks->val) == 9)
		(*echo)++;
	if (toks->type == REDIR_OUT || toks->type == REDIR_IN)
		*redir = 1;
	if (*redir && toks->type == COM)
		*redir = 0;
}

int	ft_loop_new_com_tok(char **strs, t_tokens *toks, int i, int y)
{
	int	ind;
	int	echo;
	int	redir;

	ind = 1;
	if (i)
		ind = 0;
	echo = 0;
	redir = 0;
	while (strs[i][y])
	{
		ft_if_echo_redir(&echo, &redir, toks, ind);
		if (echo)
			toks->next = ft_new_token(i, &y, strs, redir);
		else
			toks->next = ft_new_token(i, &y, strs, -1);
		if (!toks->next)
			return (1);
		ft_assign_prev_cur_tok(&toks);
		ind++;
	}
	return (0);
}

t_tokens	*ft_gimme_tokens(char **strs)
{
	int			i;
	int			y;
	t_tokens	*toks;
	t_tokens	*head;

	y = 0;
	toks = ft_new_token(0, &y, strs, -1);
	if (!toks)
		return (ft_free_toks(toks));
	toks->prev = NULL;
	toks->next = NULL;
	i = 0;
	head = toks;
	while (strs[i])
	{
		if (ft_loop_new_com_tok(strs, toks, i, y))
			return (ft_free_toks(toks));
		y = 0;
		i++;
		while (toks->next)
			toks = toks->next;
	}
	return (head);
}
