#include "minishell.h"

t_tokens	*ft_too_many_args(t_tokens *toks_orig, int i, int limit, char *com)
{
	t_tokens	*ret;
	t_tokens	*toks;

	toks = toks_orig;
	while (toks->ind_command != i)
		toks = toks->next;
	toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
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
