#include "../incl/minishell.h"

int quote_error_message(void)
{
    write(2, "Quote error\n", 13);
    return (1);
}

int	double_q_sandwich(char *s, int i)
{
	int	sandwiches;
	int	j;

	j = i;
	sandwiches = 0;
	while (i-- > 1)
    {
		if (s[i] == '"')
			sandwiches = 1;
    }
	while (s[j++] != '\0')
    {
		if (s[j] == '"' && sandwiches == 1)
			sandwiches = 2;
    }
	if (sandwiches == 2)
		return (0);
	return (1);
}

int	count_index(char *str, int last_inx)
{
	int	i;
	int	count;

	i = last_inx - 1;
	count = 0;
	if (last_inx <= 0)
		return (count);
	while (str[i] != -1)
	{
		if (str[i] == 92)
			count++;
		else if (str[i] != 92)
			return (count);
		i--;
	}
	return (count);
}

char	count_quotes(char *s, int sq, int dq)
{
	int	sq_count;
	int	dq_count;
	int	i;

	i = -1;
	sq_count = 0;
	dq_count = 0;
	while (s[++i])
	{
		if (s[i] == sq || (s[i] == 92 && s[i + 1] != '\0'
				&& s[i + 1] == sq && count_index(s, i) % 2 == 0))
		{
			if (double_q_sandwich(s, i) == 1)
				sq_count++;
		}
		else if (s[i] == dq || (s[i] == 92 && s[i + 1] != '\0'
				&& s[i + 1] == dq && count_index(s, i) % 2 == 0))
			dq_count++;
	}
	if (sq_count % 2 != 0)
		return (quote_error_message(), 1);
	else if (dq_count % 2 != 0)
		return (quote_error_message(), 1);
	return (0);
}

int	are_quotes_closed(char *str)
{
	if (count_quotes(str, '\'', '"') == 0)
		return (0);
	return (1);
}

int	cases_for_quote(char *str, int i, int double_q, int single_q)
{
	int	j;

	j = i;
	while (i != -1)
	{
		if (str[i] == '\'' && count_index(str, i) % 2 == 0)
			single_q++;
		if (str[i] == '"' && count_index(str, i) % 2 == 0)
			double_q++;
		i--;
	}
	if (single_q == 1 && double_q == 0)
		return (0);
	else if (single_q == 2 && double_q == 1)
		return (1);
	else if (single_q == 1 && double_q == 1 && str[j - 1] == '"')
		return (0);
	else if (single_q == 1 && double_q == 2 && str[j - 1] == '\'')
		return (0);
	else if (single_q == 4 && double_q == 3)
		return (0);
	else if (single_q == 2 && double_q == 2 && str[j - 1] == '\'' && str[j - 3] == '\'')
		return (0);
	return (1);
}

int	handle_quote(char *str, int i)
{
	int		single_q;
	int		double_q;
    int     re;
	int		j;

	/* move this to main -> handle_quote: if (i == 0) return (1);
    if (i == 0)
		return (1);*/
	j = i;
	if (i > 0 && (str[i + 1] == '"' || str[i + 1] == '\''))
		return (0);
    re = 0;
	while (j != 0)
	{
		if (str[j] == '\'' || str[j] == '"')
		{
            re = 1;
            break;
        }
		j--;
	}
	double_q = 0;
	single_q = 0;
	if (re == 0)
		if (cases_for_quote(str, i, double_q, single_q) == 0)
			return (0);
	return (1);
}
