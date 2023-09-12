/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/28 16:44:49 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bpfree(t_pipex *list, int i)
{
	if (list->here_doc)
		unlink(".heredoc");
	while (i < list->n)
	{
		close(list->pipes[i][0]);
		close(list->pipes[i][1]);
		//wait(NULL);
		i++;
	}
	i = 0;
	close(list->file1);
	close(list->file2);
	while (list->com_paths[i])
	{
		free(list->com_paths[i]);
		i++;
	}
	free(list->com_paths);
	i = 0;
	while (i < list->n)
	{
		free(list->pipes[i]);
		i++;
	}
	free(list->pipes);
}

void	ft_unlink(t_pipex *list, char **av, int perror)
{
	int	i;

	i = 0;
	if (!ft_strncmp("here_doc", av[1], 9))
		unlink(".heredoc");
	if (perror > 0)
		perror_bmsg("heredoc", 0, list, -1);
	if (perror < 0)
	{
		close(list->file1);
		close(list->file2);
	}
	if (perror <= -2)
	{
		while (list->com_paths[i])
		{
			free(list->com_paths[i]);
			i++;
		}
		free(list->com_paths);
	}
	if (perror <= -3)
		free(list->pids);
	if (perror != -4)
		exit (1);
}

int	**ft_gimme_pipes(t_pipex *list, char **av)
{
	int	**pipes;
	int	i;

	pipes = malloc(list->n * sizeof(int *));
	if (pipes == NULL)
		ft_unlink(list, av, -3);
	i = -1;
	while (++i < list->n && pipes != NULL)
	{
		pipes[i] = calloc(2, sizeof(int));
		if (pipes[i] == NULL)
		{
			if (i)
				while (--i)
					free(pipes[i]);
			if (pipes[0])
				free(pipes[0]);
			free(pipes);
			ft_unlink(list, av, -3);
		}
	}
	return (pipes);
}

void	free_pipes(int i, t_pipex *list, char **av, int exitt)
{
	if (i)
		while (--i)
			free(list->pipes[i]);
	if (list->args)
	{
		while (list->args[i])
		{
			free(list->args[i]);
			i++;
		}
		free(list->args);
	}
	if (list->pipes[0])
		free(list->pipes[0]);
	free(list->pipes);
	ft_unlink(list, av, -4);
	if (exitt > 0)
		exit (1);
}

void	ft_check_child(int i, t_pipex *list)
{
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

char	*ft_bcheck_paths(char **envp)
{
	while (envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			return (*envp + 5);
		envp++;
	}
	write(2, "Path not found in envs\n", 23);
	exit(1);
}

void	perror_bmsg(char *error, int j, t_pipex *list, int i)
{
	if (i == -1)
	{
		perror(error);
		exit (1);
	}
	while (j < list->n)
	{
		if (i != j)
			close(list->pipes[j][0]);
		if (i + 1 != j)
			close(list->pipes[j][1]);
		j++;
	}
}

char	*ft_gimme_command(char *command, t_pipex *list)
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
