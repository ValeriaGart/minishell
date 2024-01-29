/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:12:11 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 12:12:08 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char **ft_assign_env_lines(t_env *env_list, char **env_twod, int i)
{
	while (env_list->next)
	{
		env_twod[++i] = ft_strdup(env_list->str);
		if (!env_twod[i])
		{
			while (i >= 0)
				free(env_twod[--i]);
			free(env_twod);
			return (NULL);
		}
		env_list = env_list->next;
	}
	env_twod[++i] = NULL;
	return (env_twod);
}

char **ft_env_to_twod_arr(t_env *env_list)
{
	char **env_twod;
	int i;
	t_env *rem_env;

	i = -1;
	rem_env = env_list;
	while (rem_env)
	{
		rem_env = rem_env->next;
		i++;
	}
	env_twod = malloc(sizeof(char *) * (i + 1));
	if (env_twod == NULL)
		return (NULL);
	i = -1;
	env_twod = ft_assign_env_lines(env_list, env_twod, i);
	return (env_twod);
}

int ft_right_out(t_pipex *list, int i)
{
	if (list->redir_out > 0)
		return (list->redir_out);
	if (list->ac == 1)
		return (1);
	if (i == 0)
		return (list->pipes[1]);
	else if (i != list->ac - 1 && i != 0)
		return (list->pipes[1]);
	return (1);
}

void ft_dup_right_ends(int i, t_pipex *list)
{
	if (i == 0)
	{
		if (list->redir_out < 0)
			dup2(list->pipes[1], STDOUT_FILENO);
		close(list->pipes[1]);
		close(list->pipes[0]);
	}
	else if (i != list->ac - 1 && i != 0)
	{
		if (list->redir_out < 0)
			dup2(list->pipes[1], STDOUT_FILENO);
		if (list->redir_in < 0)
			dup2(list->rem_fd, STDIN_FILENO);
		close(list->rem_fd);
		close(list->pipes[0]);
		close(list->pipes[1]);
	}
	else
	{
		if (list->redir_in < 0)
			dup2(list->rem_fd, STDIN_FILENO);
		close(list->rem_fd);
	}
}

void ft_check_kid(int i, t_pipex *list)
{
	if (list->redir_out > 0)
	{
		dup2(list->redir_out, STDOUT_FILENO);
		close(list->redir_out);
	}
	if (list->redir_in > 0)
	{
		dup2(list->redir_in, STDIN_FILENO);
		close(list->redir_in);
	}
	if (list->ac == 1)
		return;
	ft_dup_right_ends(i, list);
}
