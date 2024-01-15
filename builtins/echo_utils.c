#include "../incl/minishell.h"

int	ft_end_space(t_tokens *toks, int i)
{
	if (toks->type != SEP)
		return (0);
	toks = toks->next;
	while (toks && toks->ind_command == i)
	{
		if (toks->type == COM)
			return (0);
		toks = toks->next;
	}
	return (1);
}

int	ft_is_nflag_echo(t_tokens *toks)
{
	int		y;
	int		q;

	y = 0;
	q = 0;
	if (toks->type != COM)
		return (0);
	if (toks->val[0] == S || toks->val[0] == D)
		q = toks->val[0];
	while (toks->val[y] == q)
		y++;
	if (toks->val[y] && toks->val[y] == '-')
	{
		y++;
		if (!toks->val[y] || toks->val[y] != 'n')
			return (0);
		while (toks->val[y] && toks->val[y] == 'n')
			y++;
		while (toks->val[y] && q && toks->val[y] == q)
			y++;
		if (!toks->val[y])
			return (1);
	}
	return (0);
}

int	ft_n_flag_echo(int i, t_tokens **toks, t_pipex *list)
{
	t_tokens	*toks_start;

	toks_start = list->tokens;
	if (!ft_is_nflag_echo(*toks))
		return (0);
	toks_start = ft_point_to_needed_tok(toks_start, i, 1, 0);
	while (toks_start != *toks)
	{
		if (toks_start->type == COM && !ft_is_nflag_echo(toks_start))
			return (0);
		toks_start = toks_start->next;
	}
	list->n_flag_echo = 1;
	if ((*toks)->next && (*toks)->next->ind_command == i
		&& (*toks)->next->type == SEP)
		*toks = (*toks)->next;
	return (1);
}
