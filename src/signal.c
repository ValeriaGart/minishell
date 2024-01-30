/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynguyen <ynguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:30 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 19:36:01 by ynguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	allocate_sig(t_pipex **list, int *i)
{
	if ((*list)->ac == 1 && is_builtin((*list)->tokens, *i))
		sig_handel(1, (*list)->data);
	else
		sig_handel(2, (*list)->data);
}

void	get_sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell = sig;
		printf("goes here \n");
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	get_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell = sig;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

void	sig_handel(int sig, t_data *data)
{
	g_minishell = 0;
	if (sig == 1)
	{
		signal(SIGINT, get_sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (sig == 3)
	{
		signal(SIGINT, get_sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (g_minishell == SIGINT)
		data->exit_code = 130;
	if (g_minishell == SIGQUIT)
		data->exit_code = 131;
}
