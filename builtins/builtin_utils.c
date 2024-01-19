#include "minishell.h"

bool	ft_last_pipe(t_tokens *toks, int i)
{
	while (toks && toks->next)
		toks = toks->next;
	if (toks && toks->ind_command == i)
		return (true);
	return (false);
}

t_tokens	*ft_point_to_needed_tok(t_tokens *toks, int i,
								int next, int skip_char)
{
	if (skip_char)
	{
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
		return (toks);
	}
	while (toks && toks->ind_command != i)
		toks = toks->next;
	if (toks && next)
		toks = toks->next;
	return (toks);
}

t_tokens	*ft_too_many_args(t_tokens *toks_orig, int i, int limit, char *com)
{
	t_tokens	*ret;
	t_tokens	*toks;

	toks = toks_orig;
	toks = ft_point_to_needed_tok(toks, i, 1, 0);
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	ret = toks;
	limit--;
	if (!toks || toks->ind_command != i)
		return (toks_orig);
	if (toks->next)
		toks = toks->next;
	while (toks && toks->ind_command == i)
	{
		if (toks->type != SEP)
			limit--;
		if (limit)
		{
			g_minishell = 1;
			ft_error(com, ": too many arguments\n", 0);
			return (NULL);
		}
		toks = toks->next;
	}
	return (ret);
}
