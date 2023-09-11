/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:03:57 by vharkush          #+#    #+#             */
/*   Updated: 2023/09/05 11:49:57 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gimme_com(char *command, t_pipex *list)
{
	char	*temp;
	char	*ret;
	char	**iter;

	if (!command)
		return (NULL);
	iter = list->com_paths;
	while (*iter)
	{
		temp = ft_strjoin(*iter, "/");
		ret = ft_strjoin(temp, command);
		free(temp);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		iter++;
	}
	return (NULL);
}

void	ft_check_kid(int i, t_pipex *list)
{
	if (list->n == 1)
		return;
	if (i == 0)
	{
		dup2(list->pipes[0][1], STDOUT_FILENO);
		close(list->pipes[0][1]);
	}
	else if (i != list->n - 1 && i != 0)
	{
		dup2(list->pipes[0][1], STDOUT_FILENO);
		dup2(list->pipes[0][0], STDIN_FILENO);
	}
	else
	{
		dup2(list->pipes[0][0], STDIN_FILENO);
		close(list->pipes[0][1]);
		dup2(list->file2, STDOUT_FILENO);
 	}
}

void    ft_loop_kids(t_pipex *list, int i, char **env, char **av)
{
	ft_check_kid(i, list);
	list->args = ft_split(av[i], ' ');
	if (list->args)
		ft_check_builtins(env, list);
    if (list->args)
		list->command = ft_gimme_com(list->args[0], list);
	else
		list->command = NULL;
	if (i == 0 && list->n != 1)
		close(list->pipes[0][1]);
	else if (i != list->n - 1  || list->n == 1)
	{
		close(list->pipes[0][1]);
		close(list->pipes[0][0]);
	}
	else if (list->n != 1)
		close(list->pipes[0][0]);
	if (list->args)
		execve(list->command, list->args, env);
	exit(0);
}

void	ft_this_next_pipes(t_pipex *list, int i)
{
	if (i % 2)
	{
		list->this_pipe = 1;
		list->next_pipe = 0;
	}
	else
	{
		list->this_pipe = 0;
		list->next_pipe = 1;
	}
}

void    ft_do_all_to_exec(t_pipex *list, char **env, char **av)
{
	int	i;

    list->pipes = malloc(sizeof(int *));
	if (list->pipes)
		list->pipes[0] = ft_calloc(2, sizeof(int));
	i = -1;
	while (++i < list->n)
	{
		ft_this_next_pipes(list, i);
		pipe(list->pipes[0]);
		list->pids[i] = fork();
        if (list->pids[i] == 0)
			ft_loop_kids(list, i, env, av);
		close(list->pipes[0][0]);
		close(list->pipes[0][1]);
		wait(NULL);
    }
}

void	ft_exec(char **env, int ac, char **av, t_data *data)
{
    t_pipex	list;
	pid_t	*pids;

	list.data = data;
    list.paths = ft_bcheck_paths(env);
    list.com_paths = ft_split(list.paths, ':');
    list.n = ac;
    pids = malloc(list.n * sizeof(pid_t));
    list.pids = pids;
    list.file1 = 0;
    list.file2 = 1;
    ft_do_all_to_exec(&list, env, av);
    //ft_bpfree(&list, 0);
	free(pids);
}
