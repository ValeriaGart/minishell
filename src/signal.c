
#include "../incl/minishell.h"

void	get_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		minishell_global = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
