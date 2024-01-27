/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_n_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:55 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:14:56 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_bcheck_paths(t_env	*env)
{
	while (env->next)
	{
		if (!ft_strncmp("PATH", env->str, 4))
			return (ft_strdup(env->str + 5));
		env = env->next;
	}
	return (ft_strdup("./"));
}

void	ft_wait_for_my_babies(t_pipex *list, int status)
{
	int	i;

	i = -1;
	if (g_minishell == 131)
		g_minishell = 0;
	while (++i < list->ac)
	{
		if (list->ac != 1 || !is_builtin(list->tokens, i))
			waitpid(list->pids[i], &status, 0);
		if ((list->ac != 1 || !is_builtin(list->tokens, i))
			&& WIFEXITED(status))
			g_minishell = WEXITSTATUS(status);
		else if ((list->ac != 1 || !is_builtin(list->tokens, i))
			&& WIFSIGNALED(status))
		{
			if (!g_minishell && WTERMSIG(status) == SIGINT)
			{
				g_minishell = 130;
				write(1, "\n", 1);
			}
		}
	}
	if (list->heredoc_c)
		g_minishell = 130;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((s1[i]) - s2[i]);
}
