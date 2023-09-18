#include "../incl/minishell.h"

int quote_exist(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\'' || s[i] != '\"')
			return (1);
		i++;
	}
	return (0);
}

int	ft_execute_symbols(char *str, int exc, int i)
{
	int	j;
    int n;

	if (exc == 1)
		return (i + 1);
	j = exc;
	if (exc % 2 == 0)
		while (j-- != exc / 2)
			write(1, "\\", 1);
	else
	{
		j = exc;
		while (j-- != (exc / 2) + 1)
			write(1, "\\", 1);
	}
    n = i + exc;
	return (n);
}

void	no_quote_execute(char *s, int i, int j, int double_q)
{
	int	q;

	q = quote_exist(s);
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			double_q = 1;
		if ((s[i] == ' ' && s[i + 1] == ' ' && q == 1) || s[i] == '\'')
			while (s[i] == ' ')
				i++;
		j = i;
		if (s[i] == '\'')
		{
			while (s[j] == '\'')
				j++;
			i = ft_execute_symbols(s, j, i);
		}
		if (s[i] != '"' && s[i] != 39)
			printf("%c", s[i]);
		else if (s[i] == 39)
			if (double_q == 1)
				printf("%c", s[i]);
		i++;
	}
}


int inx_in_quote(char *s, int inx)
{
	int	quotes;

	if (s[inx] != 39 && s[inx] != 34)
		return (inx);
	quotes = s[inx + 1];
	while (s[inx] != quotes && count_index(s, inx) % 2 == 0)
	{
		if (s[inx] == '\0')
			return (inx);
		inx++;
	}
	return (inx);
}

int quote_n_pipe(char *s, int inx, int start, int end)
{
    char	**tokens;
	char	*tmp;

	if (!s)
		return (1);
	tokens = malloc(sizeof(char *) * (count_pipes(s) + 1));
	if (!tokens)
		return (1);
	while (s[++end] != '\0')
	{
		end = skip_quotes(s, end);
		if (ft_strlen(s) > end && s[end] != '\0'
			&& s[end] == '|' && s[end - 1] != 39
			&& nb_esc_chars(s, end) % 2 == 0)
		{
			tmp = ft_sdup2(s, start, end);
			tokens[++inx] = ft_strtrim(tmp, 32);
			free(tmp);
			start = end + 1;
		}
	}
	tmp = ft_strdup2(s, start, end);
	tokens[++inx] = ft_strtrim(tmp, 32);
	tokens[++inx] = '\0';
	return (free(tmp), tokens);
}
