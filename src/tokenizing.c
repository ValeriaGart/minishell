#include "../incl/minishell.h"

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

int		ft_quotecho_condition(char **val, int y, char *str, int *i)
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
int		ft_quote_condition(char **val, int y, char *str, int *i)
{
	char	*value;
	char	meet_again;

	meet_again = str[y];
	value = *val;
	y++;
	while (str[y] != meet_again)
	{
		*i = *i + 1;
		value[*i] = str[y];
		y++;
	}
	y++;
	return (y);
}

char	*ft_tok_val(char *str, int *y, int echo)
{
	char	*value;
	int		i;
	int		rem;

	i = *y;
	if (str[i] && (str[i] == ' ' || str[i] == '<'
		|| str[i] == '>'))
		return (ft_val_is_not_a_word(str, y));
	while (str[i] && str[i] != ' ' && str[i] != '<'
			&& str[i] != '>')
	{
		if (str[i] == S || str[i] == D)
		{
			rem = str[i];
			i++;
			while (str[i] != rem)
				i++;
		}
		i++;
	}
	i = i - *y;
	value = ft_calloc(sizeof(char), i + 1);
	i = -1;
	if (!value)
		return (NULL);
	while (str[*y] && str[*y] != ' ' && str[*y] != '<'
			&& str[*y] != '>')
	{
		if ((str[*y] == S || str[*y] == D) && echo)
			*y = ft_quotecho_condition(&value, *y, str, &i);
		else if (str[*y] == S || str[*y] == D)
			*y = ft_quote_condition(&value, *y, str, &i);
		else
		{
			value[++i] = str[*y];
			++(*y);
		}
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
		if (value[1] && value[1] == '<')
			type = HERE_DOC;
		else
			type = REDIR_IN;
	}
	else
		type = COM;
	return (type);
}

t_tokens	*ft_new_echo_token(int i, int ind, int *y, char **strs)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens));
	if (!new_tok)
		return (NULL);
	new_tok->val = ft_tok_val(strs[i], y, 1);
	if (!new_tok->val)
		return (NULL);
	new_tok->type = ft_tok_type(new_tok->val);
	new_tok->ind_command = i;
	new_tok->ind_word = ind;
	return (new_tok);
}

t_tokens	*ft_new_token(int i, int ind, int *y, char **strs)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens));
	if (!new_tok)
		return (NULL);
	new_tok->val = ft_tok_val(strs[i], y, 0);
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
	while (toks && toks->next)
		toks = toks->next;
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

int			ft_loop_new_com_tok(char **strs, t_tokens *toks, int i, int y)
{
	int	ind;
	int echo;

	ind = 1;
	if (i)
		ind = 0;
	echo = 0;
	while (strs[i][y])
	{
		if (toks->type == COM && !ft_strncmp(toks->val, "echo", 4) && ind < 2 && ft_strlen(toks->val) == 4)
			echo++;
		if (echo)
			toks->next = ft_new_echo_token(i, ind, &y, strs);
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
		toks = head;
		while (toks->next)
			toks = toks->next;
	}
	return (head);
}
