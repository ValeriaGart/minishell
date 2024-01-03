#include "../incl/minishell.h"

int	ft_pre_tok_check(int *i, char *str)
{
	int		rem;

	rem = 0;
	if (str[*i] && (str[*i] == ' ' || str[*i] == '<' || str[*i] == '>'))
		return (1);
	while (str[*i] && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == S || str[*i] == D)
		{
			rem = str[*i];
			(*i)++;
			while (str[*i] != rem)
				(*i)++;
		}
		(*i)++;
	}
	return (0);
}

char	*ft_tok_val(char *str, int *y, int echo, int redir)
{
	char	*value;
	int		i;

	i = *y;
	if (ft_pre_tok_check(&i, str))
		return (ft_val_is_not_a_word(str, y));
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

bool	ft_type_redir(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	if (str[i])
		return (false);
	return (true);
}

int	ft_tok_type(char *value)
{
	int	type;

	type = 0;
	if (value[0] == '\0')
		type = EMPTY_STR;
	else if (value[0] == ' ')
		type = SEP;
	else if (ft_type_redir(value, '>') == true)
		type = REDIR_OUT;
	else if (ft_type_redir(value, '<') == true)
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
