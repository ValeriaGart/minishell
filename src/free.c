#include "../incl/minishell.h"

int	free_n_exit(t_data *d, int i)
{
	// ft_free_prompt(d);
	// ft_freelist(d->exp);
	// if (d->start != NULL)
	// 	ft_freetoken(d->start);
	// free_stuff(d->path);
	if (d->pid != NULL)
		free(d->pid);
	free(d);
	if (i == 127)
		ft_putstr_fd(": Change other commands, mate\n", 2);
	rl_clear_history();
	exit(i);
}

