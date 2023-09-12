
#include "../incl/minishell.h"

void	get_sigint(int sig)
{
	if (sig == SIGINT)
	{
		exit(0);
		minishell_global = 130;
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
