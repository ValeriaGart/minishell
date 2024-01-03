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

	y = 0;
	if (toks->type != COM)
		return (0);
	if (ft_strlen(toks->val) == 2)
		y = 1;
	if (ft_strlen(toks->val) == 4 && (toks->val[0] == S || toks->val[0] == D))
		y = 2;
	if (y && toks->val[y - 1] == '-' && toks->val[y] == 'n')
		return (1);
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
