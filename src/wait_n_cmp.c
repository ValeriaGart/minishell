/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_n_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynguyen <ynguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:55 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 19:41:15 by ynguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_change_ac_on_err(t_tokens *iter, int i)
{
	while (iter && iter->ind_command != i)
		iter = iter->next;
	while (iter && iter->ind_command == i)
	{
		iter->ind_command = -1;
		iter = iter->next;
	}
}

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

void	sig_int_quit(int status, t_pipex **list)
{
	if (!(*list)->data->exit_code && WTERMSIG(status) == SIGINT)
	{
		(*list)->data->exit_code = 130;
		write(1, "\n", 1);
	}
	else if (!(*list)->data->exit_code && WCOREDUMP(status) == SIGQUIT)
	{
		(*list)->data->exit_code = 131;
		write(1, "Quit (core dumped)\n", 20);
	}
}

void	ft_wait_for_my_babies(t_pipex *list, int status)
{
	int	i;

	i = -1;
	if (list->data->exit_code == 131)
		list->data->exit_code = 0;
	while (++i < list->ac)
	{
		if (list->ac != 1 || !is_builtin(list->tokens, i))
			waitpid(list->pids[i], &status, 0);
		if ((list->ac != 1 || !is_builtin(list->tokens, i))
			&& WIFEXITED(status))
			list->data->exit_code = WEXITSTATUS(status);
		else if ((list->ac != 1 || !is_builtin(list->tokens, i))
			&& WIFSIGNALED(status))
			sig_int_quit(status, &list);
	}
	if (list->heredoc_c)
		list->data->exit_code = 130;
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
