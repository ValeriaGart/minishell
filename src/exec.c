/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/09/04 10:47:17 by yenng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

int	**ft_gimme_pipess(t_pipex *list)
{
	int	**pipes;
	int	i;

	pipes = malloc(list->n * sizeof(int *));
	i = -1;
	while (++i < list->n && pipes != NULL)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (pipes[i] == NULL)
		{
			if (i)
				while (--i)
					free(pipes[i]);
			if (pipes[0])
				free(pipes[0]);
			free(pipes);
		}
	}
	return (pipes);
}

void	ft_check_kid(int i, t_pipex *list)
{
	if (list->n == 1)
		return;
	if (i == 0)
	{
		dup2(list->pipes[i + 1][1], STDOUT_FILENO);
		close(list->pipes[i][0]);
		close(list->pipes[i + 1][1]);
		dup2(list->file1, STDIN_FILENO);
	}
	else if (i != list->n - 1 && i != 0)
	{
		dup2(list->pipes[i + 1][1], STDOUT_FILENO);
		dup2(list->pipes[i][0], STDIN_FILENO);
		close(list->pipes[i][0]);
		close(list->pipes[i + 1][1]);
	}
	else
	{
		dup2(list->pipes[i][0], STDIN_FILENO);
		close(list->pipes[i][0]);
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
	if (list->args)
		execve(list->command, list->args, env);
	exit(0);
}

void    ft_do_all_to_exec(t_pipex *list, char **env, char **av)
{
	int	i;

    list->pipes = ft_gimme_pipess(list);
    i = -1;
    while (++i < list->n)
	    pipe(list->pipes[i]);
	i = -1;
	while (++i < list->n)
	{
		list->pids[i] = fork();
        if (list->pids[i] == 0)
			ft_loop_kids(list, i, env, av);
    }
}
 
void	ft_exec(char **env, int ac, char **av, t_data *data)
{
    t_pipex	list;
	pid_t	*pids;
	int i = 0;

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
    while (i < list.n)
	{
		close(list.pipes[i][0]);
		close(list.pipes[i][1]);
		wait(NULL);
		i++;
	}
	free(pids);
}
