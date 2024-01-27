/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:30 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:14:31 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		g_minishell = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	get_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell = 130;
		write(STDOUT_FILENO, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		g_minishell = 131;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	get_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

void	sig_handel(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, get_sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, get_sig_child);
	}
	if (sig == 3)
	{
		signal(SIGINT, get_sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
