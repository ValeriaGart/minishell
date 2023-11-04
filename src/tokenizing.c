#include "minishell.h"

void	ft_assign_prev_cur_tok(t_tokens **toks)
{
	t_tokens	*prev;

	prev = *toks;
	*toks = (*toks)->next;
	(*toks)->next = NULL;
	(*toks)->prev = prev;
}

char	*ft_val_is_not_a_word(char *str, int *y)
{
	char	*value;

	if ((str[*y] == '<' || str[*y] == '>')
		&& str[*y + 1] == str[*y])
		value = ft_calloc(sizeof(char), 3);
	else
		value = ft_calloc(sizeof(char), 2);
	if (!value)
		return (NULL);
	if (str[*y] == ' ')
	{
		while (str[*y] == ' ')
			(*y)++;
		value[0] = ' ';
		return (value);
	}
	value[0] = str[*y];
	(*y)++;
	if (str[*y - 1] == str[*y])
	{
		value[1] = str[*y];
		(*y)++;
	}
	return (value);
}

char	*ft_tok_val(char *str, int *y)
{
	char	*value;
	int		i;

	i = *y;
	if (str[i] && (str[i] == ' ' || str[i] == '<'
		|| str[i] == '>'))
		return (ft_val_is_not_a_word(str, y));
	while (str[i] && str[i] != ' ' && str[i] != '<'
			&& str[i] != '>')
		i++;
	i = i - *y;
	value = ft_calloc(sizeof(char), i + 1);
	i = -1;
	if (!value)
		return (NULL);
	while (str[*y] && str[*y] != ' ' && str[*y] != '<'
			&& str[*y] != '>')
	{
		value[++i] = str[*y];
		++(*y);
	}
	return (value);
}

int		ft_tok_type(char *value)
{
	int type;

	type = 0;
	if (value[0] == ' ')
		type = SEP;
	else if (value[0] == '>')
		type = REDIR_OUT;
	else if (value[0] == '<')
	{
		if (value[1] == '\0')
			type = REDIR_IN;
		else
			type = HERE_DOC;
	}
	else
		type = COM;
	return (type);
}

t_tokens	*ft_new_token(int i, int ind, int *y, char **strs)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens));
	if (!new_tok)
		return (NULL);
	new_tok->val = ft_tok_val(strs[i], y);
	if (!new_tok->val)
		return (NULL);
	new_tok->type = ft_tok_type(new_tok->val);
	new_tok->ind_command = i;
	new_tok->ind_word = ind;
	return (new_tok);
}

t_tokens	*ft_free_toks(t_tokens *toks)
{
	if (!toks)
		return (NULL);
	while (toks->prev)
	{
		if (toks->val)
			free(toks->val);
		toks = toks->prev;
		free(toks->next);
		toks->next = NULL;
	}
	if (toks->val)
		free(toks->val);
	free(toks);
	return (NULL);
}

t_tokens	*ft_gimme_tokens(char **strs)
{
	int			i;
	int			y;
	int			ind;
	t_tokens	*toks;
	t_tokens	*head;

	y = 0;
	ind = 0;
	toks = ft_new_token(0, ind, &y, strs);
	if (!toks)
		return (ft_free_toks(toks));
	toks->prev = NULL;
	toks->next = NULL;
	ind++;
	i = 0;
	head = toks;
	while (strs[i])
	{
		if (i)
			ind = 0;
		while (strs[i][y])
		{
			toks->next = ft_new_token(i, ind, &y, strs);
			if (!toks)
				return (ft_free_toks(toks));
			ft_assign_prev_cur_tok(&toks);
			ind++;
		}
		y = 0;
		i++;
	}
	return (head);
}
