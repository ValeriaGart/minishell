#include "../incl/minishell.h"

void	allocate_sig(t_pipex **list, int *i)
{
	if ((*list)->ac == 1 && is_builtin((*list)->tokens, *i))
		sig_handel(1);
	else
		sig_handel(2);
}

void	get_sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_minishell = 130;
	}
}

void	get_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		g_minishell = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		write(1, "\n", 2);
		g_minishell = 131;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_handel(int sig)
{
	if (sig == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, get_sig_parent);
	}
	if (sig == 2)
	{
		signal(SIGINT, get_sig_child);
		signal(SIGQUIT, get_sig_child);
	}
}
