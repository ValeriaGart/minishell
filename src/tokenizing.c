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

int	ft_tok_type(char *value)
{
	int	type;

	type = 0;
	if (value[0] == ' ')
		type = SEP;
	else if (value[0] == '>')
		type = REDIR_OUT;
	else if (value[0] == '<')
	{
		if (value[1] && value[1] == '<')
			type = HERE_DOC;
		else
			type = REDIR_IN;
	}
	else
		type = COM;
	return (type);
}

//TODO: too many arguements here <3
t_tokens	*ft_new_echo_token(int i, int ind, int *y, char **strs, int redir)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens));
	if (!new_tok)
		return (NULL);
	new_tok->val = ft_tok_val(strs[i], y, 1, redir);
	if (!new_tok->val)
	{
		free(new_tok);
		return (NULL);
	}
	new_tok->type = ft_tok_type(new_tok->val);
	new_tok->ind_command = i;
	new_tok->ind_word = ind;
	return (new_tok);
}

//TODO: overline
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
		if (toks->type == COM && !ft_strncmp(toks->val, "echo", 4)
			&& ind < 2 && ft_strlen(toks->val) == 4)
			echo++;
		if (toks->type == REDIR_OUT || toks->type == REDIR_IN)
			redir = 1;
		if (redir && toks->type == COM)
			redir = 0;
		if (echo)
			toks->next = ft_new_echo_token(i, ind, &y, strs, redir);
		else
			toks->next = ft_new_token(i, ind, &y, strs);
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
	toks = ft_new_token(0, 0, &y, strs);
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
