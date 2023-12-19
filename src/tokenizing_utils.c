#include "../incl/minishell.h"

//TODO: overline
char	*ft_tok_val(char *str, int *y, int echo, int redir)
{
	char	*value;
	int		i;
	int		rem;

	i = *y;
	if (str[i] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
		return (ft_val_is_not_a_word(str, y));
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>')
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
	while (str[*y] && str[*y] != ' ' && str[*y] != '<' && str[*y] != '>')
	{
		if ((str[*y] == S || str[*y] == D) && echo && !redir)
			*y = ft_quotecho_condition(&value, *y, str, &i);
		else if (str[*y] == S || str[*y] == D)
			*y = ft_quote_condition(&value, *y, str, &i);
		else
		{
			value[++i] = str[*y];
			*y += 1;
		}
	}
	return (value);
}

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

	if ((str[*y] == '<' || str[*y] == '>') && str[*y + 1] == str[*y])
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

t_tokens	*ft_new_token(int i, int ind, int *y, char **strs)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens));
	if (!new_tok)
		return (NULL);
	new_tok->val = ft_tok_val(strs[i], y, 0, 0);
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
